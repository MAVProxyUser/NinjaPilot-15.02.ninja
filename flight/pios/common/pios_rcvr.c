#include "pios.h"

#ifdef PIOS_INCLUDE_RCVR

#include <pios_rcvr_priv.h>

enum pios_rcvr_dev_magic {
    PIOS_RCVR_DEV_MAGIC = 0x99aabbcc,
};

struct pios_rcvr_dev {
    enum pios_rcvr_dev_magic magic;
    uint32_t lower_id;
    const struct pios_rcvr_driver *driver;
};

static bool PIOS_RCVR_validate(struct pios_rcvr_dev *rcvr_dev)
{
    return rcvr_dev->magic == PIOS_RCVR_DEV_MAGIC;
}

#if defined(PIOS_INCLUDE_FREERTOS)
static struct pios_rcvr_dev *PIOS_RCVR_alloc(void)
{
    struct pios_rcvr_dev *rcvr_dev;

    rcvr_dev = (struct pios_rcvr_dev *)pios_malloc(sizeof(*rcvr_dev));
    if (!rcvr_dev) {
        return NULL;
    }

    rcvr_dev->magic = PIOS_RCVR_DEV_MAGIC;
    return rcvr_dev;
}
#else
static struct pios_rcvr_dev pios_rcvr_devs[PIOS_RCVR_MAX_DEVS];
static uint8_t pios_rcvr_num_devs;
static struct pios_rcvr_dev *PIOS_RCVR_alloc(void)
{
    struct pios_rcvr_dev *rcvr_dev;

    if (pios_rcvr_num_devs >= PIOS_RCVR_MAX_DEVS) {
        return NULL;
    }

    rcvr_dev = &pios_rcvr_devs[pios_rcvr_num_devs++];
    rcvr_dev->magic = PIOS_RCVR_DEV_MAGIC;

    return rcvr_dev;
}
#endif /* if defined(PIOS_INCLUDE_FREERTOS) */

/**
 * Initialises RCVR layer
 * \param[out] handle
 * \param[in] driver
 * \param[in] id
 * \return < 0 if initialisation failed
 */
int32_t PIOS_RCVR_Init(uint32_t *rcvr_id, const struct pios_rcvr_driver *driver, uint32_t lower_id)
{
    PIOS_DEBUG_Assert(rcvr_id);
    PIOS_DEBUG_Assert(driver);

    struct pios_rcvr_dev *rcvr_dev;

    rcvr_dev = (struct pios_rcvr_dev *)PIOS_RCVR_alloc();
    if (!rcvr_dev) {
        goto out_fail;
    }

    rcvr_dev->driver   = driver;
    rcvr_dev->lower_id = lower_id;

    *rcvr_id = (uint32_t)rcvr_dev;
    return 0;

out_fail:
    return -1;
}

/**
 * @brief Reads an input channel from the appropriate driver
 * @param[in] rcvr_id driver to read from
 * @param[in] channel channel to read
 * @returns Unitless input value
 *  @retval PIOS_RCVR_TIMEOUT indicates a failsafe or timeout from that channel
 *  @retval PIOS_RCVR_INVALID invalid channel for this driver (usually out of range supported)
 *  @retval PIOS_RCVR_NODRIVER driver was not initialized
 */
int32_t PIOS_RCVR_Read(uint32_t rcvr_id, uint8_t channel)
{
    // Publicly facing API uses channel 1 for first channel
    if (channel == 0) {
        return PIOS_RCVR_INVALID;
    } else {
        channel--;
    }

    if (rcvr_id == 0) {
        return PIOS_RCVR_NODRIVER;
    }

    struct pios_rcvr_dev *rcvr_dev = (struct pios_rcvr_dev *)rcvr_id;

    if (!PIOS_RCVR_validate(rcvr_dev)) {
        /* Undefined RCVR port for this board (see pios_board.c) */
        PIOS_Assert(0);
    }

    PIOS_DEBUG_Assert(rcvr_dev->driver->read);

    return rcvr_dev->driver->read(rcvr_dev->lower_id, channel);
}

/**
 * @brief Reads input quality from the appropriate driver
 * @param[in] rcvr_id driver to read from
 * @returns received signal quality expressed as a %
 *  @retval PIOS_RCVR_NODRIVER driver was not initialized
 */
uint8_t PIOS_RCVR_GetQuality(uint32_t rcvr_id)
{
    if (rcvr_id == 0) {
        return PIOS_RCVR_NODRIVER;
    }

    struct pios_rcvr_dev *rcvr_dev = (struct pios_rcvr_dev *)rcvr_id;

    if (!PIOS_RCVR_validate(rcvr_dev)) {
        /* Undefined RCVR port for this board (see pios_board.c) */
        /* As no receiver is available assume min */
        return 0;
    }

    if (!rcvr_dev->driver->get_quality) {
        /* If no quality is available assume max */
        return 100;
    }

    return rcvr_dev->driver->get_quality(rcvr_dev->lower_id);
}

/**
 * @brief Get a semaphore that signals when a new sample is available.
 * @param[in] rcvr_id driver to read from
 * @param[in] channel channel to read
 * @returns The semaphore, or NULL if not supported.
 */
xSemaphoreHandle PIOS_RCVR_GetSemaphore(uint32_t rcvr_id, uint8_t channel)
{
    // Publicly facing API uses channel 1 for first channel
    if (channel == 0) {
        return NULL;
    } else {
        channel--;
    }

    if (rcvr_id == 0) {
        return NULL;
    }

    struct pios_rcvr_dev *rcvr_dev = (struct pios_rcvr_dev *)rcvr_id;

    if (!PIOS_RCVR_validate(rcvr_dev)) {
        /* Undefined RCVR port for this board (see pios_board.c) */
        PIOS_Assert(0);
    }

    if (rcvr_dev->driver->get_semaphore) {
        return rcvr_dev->driver->get_semaphore(rcvr_dev->lower_id, channel);
    }
    return NULL;
}

#endif /* PIOS_INCLUDE_RCVR */

/**
 * @}
 * @}
 */

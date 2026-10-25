/* Keep the UAVObject handle table as its own output section, in writable RAM.
 *
 * Two things have to be true at once, and it took a boot loop and a silent
 * failure to establish both:
 *
 * 1. The section must be WRITABLE. Each generated UAVObject declares
 *      static UAVObjHandle handle __attribute__((section("_uavo_handles")));
 *    and UAVObjInitialize() memset()s the whole region to zero before use.
 *    ESP-IDF has no placement rule for the name, so as an orphan it landed in
 *    flash-mapped rodata at 0x3f40xxxx and the memset died with a
 *    LoadStoreError -- a boot loop, ~19 resets in 12 seconds.
 *
 * 2. The OUTPUT SECTION MUST KEEP THE NAME `_uavo_handles`. GNU ld only
 *    auto-generates __start__uavo_handles / __stop__uavo_handles for an output
 *    section whose name is a valid C identifier, and uavobjectmanager.c walks
 *    the table between exactly those two symbols. Merging the input into
 *    .dram0.data (e.g. via an IDF .lf fragment) fixes the fault but loses the
 *    boundary symbols -- and because uavobjectprivate.h declares them weak,
 *    that links cleanly and then finds ZERO objects at runtime. Silent, and
 *    much worse than the crash.
 *
 * INSERT AFTER is not usable here: ESP-IDF supplies its script via -T, and
 * ld's INSERT only augments the *default* script ("`.dram0.bss` not found for
 * insert"). A plain SECTIONS block works instead, because ld combines the
 * SECTIONS commands from all the -T scripts it is given -- which is already
 * how IDF passes memory.ld and sections.ld together.
 */
SECTIONS
{
  _uavo_handles :
  {
    . = ALIGN(4);
    KEEP(*(_uavo_handles))
    . = ALIGN(4);
  } > dram0_0_seg
}

/* And now move the heap out of the way.
 *
 * ESP-IDF captures `_heap_low_start = ABSOLUTE(.)` near the end of its own
 * sections.ld, and memory.ld does `_heap_start = _heap_low_start`. Because
 * ld appends the -T scripts in order, OUR section is placed after that
 * capture -- so without this the heap begins at exactly
 * __start__uavo_handles and malloc hands out the handle table. (Verified:
 * _heap_start and __start__uavo_handles both read 0x3ffb3d30.)
 *
 * Linker-script symbol assignments are ordered expressions, not object
 * symbols, so re-assigning here is legal and this later value is the one
 * that survives. The semantics are exactly what we want: this DRAM is
 * spoken for, start the heap above it.
 */
_heap_start = ALIGN(ADDR(_uavo_handles) + SIZEOF(_uavo_handles), 16);

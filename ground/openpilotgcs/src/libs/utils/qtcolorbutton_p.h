#ifndef QTCOLORBUTTON_P_H
#define QTCOLORBUTTON_P_H

#include "qtcolorbutton.h"
#include <QColor>
#include <QPoint>
#include <QPixmap>

namespace Utils {

class QtColorButtonPrivate {
    QtColorButton *q_ptr;
    Q_DECLARE_PUBLIC(QtColorButton)
public:
    QColor m_color;
#ifndef QT_NO_DRAGANDDROP
    QColor m_dragColor;
    QPoint m_dragStart;
    bool m_dragging;
#endif
    bool m_backgroundCheckered;
    bool m_alphaAllowed;

    void slotEditColor();
    QColor shownColor() const;
    QPixmap generatePixmap() const;
    
    QtColorButtonPrivate(QtColorButton *q) : q_ptr(q), m_backgroundCheckered(true), m_alphaAllowed(true)
    {
#ifndef QT_NO_DRAGANDDROP
        m_dragging = false;
#endif
    }
};

} // namespace Utils

#endif // QTCOLORBUTTON_P_H
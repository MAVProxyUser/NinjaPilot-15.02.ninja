#ifndef QTCOLORBUTTON_P_H
#define QTCOLORBUTTON_P_H

#include <QColor>
#include <QPoint>

class QPixmap;

namespace Utils {

class QtColorButton;

class QtColorButtonPrivate
{
public:
    QtColorButton *q_ptr;
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
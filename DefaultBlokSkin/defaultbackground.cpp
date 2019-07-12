#include "defaultbackground.h"

DefaultBackground::DefaultBackground()
{

}

QPixmap DefaultBackground::pixmap()
{
    return QPixmap(":/resources/images/background.png");
}

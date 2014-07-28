#include "../include/qsfmlcanvas.hpp"

#ifdef Q_WS_X11
  #include <Qt/qx11info_x11.h>
  #include <X11/Xlib.h>
#endif

QSFMLCanvas::QSFMLCanvas(QWidget* parent, const QPoint& position, const QSize& size, unsigned int frameTime) :
  QWidget (parent), simInitialized(false)
{
  setAttribute(Qt::WA_PaintOnScreen);
  setAttribute(Qt::WA_OpaquePaintEvent);
  setAttribute(Qt::WA_NoSystemBackground);

  setFocusPolicy(Qt::StrongFocus);
  
  move(position);
  resize(size);

  simTimer.setInterval(frameTime);
}

QSFMLCanvas::~QSFMLCanvas()
{
  ///// 
}

void QSFMLCanvas::OnInit()
{
  //to be overridden in children
}

void QSFMLCanvas::OnUpdate()
{
  //^^^^
}

void QSFMLCanvas::showEvent(QShowEvent*)
{
  if (!simInitialized)
    {
#ifdef Q_WS_X11
      XFlush(QX11Info::display());
#endif
      QWidget::create(winId());

      OnInit();
      
      connect(&simTimer, SIGNAL(timeout()), this, SLOT(repaint()));
      simTimer.start();

      simInitialized = true;
    }
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
  return 0;
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
  OnUpdate();
  display();
}

#ifndef QSFMLCANVAS_HPP
#define QSFMLCANVAS_HPP

#include <QtGui>
#include <SFML/Graphics.hpp>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
public:
  QSFMLCanvas(QWidget* parent, const QPoint& position, const QSize& size, unsigned int frameTime = 0);
private:
  virtual void OnInit();
  virtual void OnUpdate();
  virtual QPaintEngine* paintEngine() const;
  virtual void showEvent(QShowEvent*);
  virtual void paintEvent(QPaintEvent*);

  QTimer simTimer;
  bool simInitialized;
};

#endif

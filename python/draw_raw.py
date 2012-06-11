from pylab import *
import serial
import re
import pygame
from OpenGL.GL import *
from OpenGL.GLU import *

s = serial.Serial('/dev/ttyUSB0', 38400)

def readData(ser):
  line = ser.readline()
  vals = re.search('([0-9-]+), ([0-9-]+), ([0-9-]+), ([0-9-]+), ([0-9-]+), ([0-9-]+)', line)
  try:
    result = (float(vals.group(1)), float(vals.group(2)), float(vals.group(3)), float(vals.group(4)), float(vals.group(5)), float(vals.group(6)))
  except:
    result = (0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
  return array(result)

def makeangles(raw, scale=2000, fs = 100):
  return raw * scale / (32768.0 * fs)

def makeaccel(raw, max_g = 16.0):
  return raw * 0.0039;

ion()

try:
  x = zeros((100))
  y = zeros((100))
  z = zeros((100))
  x[99] = -3
  x[98] = 3
#  lx, = plot(range(100), x)
#  hold(True)
#  ly, = plot(range(100), y)
#  lz, = plot(range(100), z)
#  show()
  rot = identity(3)
  i = 0

  pygame.init()
  pygame.display.set_mode((600,400), pygame.OPENGL | pygame.DOUBLEBUF)

  glNewList(1,GL_COMPILE)

  glBegin(GL_QUADS)
  
  glColor3f(1,0,0)
  glNormal3f(0,0,-1)
  glVertex3f( -1, -1, -1)
  glVertex3f( 1, -1, -1)
  glVertex3f( 1, 1, -1)
  glVertex3f( -1, 1, -1)

  glColor3f(0,1,0)
  glNormal3f(0,0,1)
  glVertex3f( -1, -1, 1)
  glVertex3f( 1, -1, 1)
  glVertex3f( 1, 1, 1)
  glVertex3f( -1, 1, 1)

  glColor3f(0,0,1)
  glNormal3f(0,-1,0)
  glVertex3f( -1, -1, -1)
  glVertex3f( 1, -1, -1)
  glVertex3f( 1, -1, 1)
  glVertex3f( -1, -1, 1)

  glColor3f(1,1,0)
  glNormal3f(0,1,0)
  glVertex3f( -1, 1, -1)
  glVertex3f( 1, 1, -1)
  glVertex3f( 1, 1, 1)
  glVertex3f( -1, 1, 1)

  glColor3f(1,0,1)
  glNormal3f(-1,0,0)
  glVertex3f( -1, -1, -1)
  glVertex3f( -1, 1, -1)
  glVertex3f( -1, 1, 1)
  glVertex3f( -1, -1, 1)

  glColor3f(0,1,1)
  glNormal3f(1,0,0)
  glVertex3f( 1, -1, -1)
  glVertex3f( 1, 1, -1)
  glVertex3f( 1, 1, 1)
  glVertex3f( 1, -1, 1)

  glEnd()
  glEndList()
  glEnable(GL_DEPTH_TEST)
  glDepthFunc(GL_LEQUAL)
  acc = array([0,0,1])

  while True:
    raw = readData(s)
    angle = makeangles(raw[0:3]) * pi / 180.0
    accel = makeaccel(raw[3:])
    mag = sqrt(dot(accel, accel))
#    print accel
#    print sqrt(dot(accel, accel))

    # Angle adjustment
    rm = transpose(array([[1,-angle[2],angle[1]],[angle[2],1,-angle[0]],[-angle[1],angle[0],1]]));
    rot = dot(rot, rm)

    # Re-Ortho-and-Normalization
    error = dot(rot[:, 0], rot[:, 1])
    rot_new = rot
    rot_new[:, 0] = rot[:, 0] - (error / 2.0) * rot[:, 1]
    rot_new[:, 1] = rot[:, 1] - (error / 2.0) * rot[:, 0]
    rot_new[:, 2] = cross(rot_new[:, 0], rot_new[:, 1])
    rot[:, 0] = 0.5 * (3.0 - dot(rot_new[:, 0], rot_new[:, 0])) * rot_new[:, 0]
    rot[:, 1] = 0.5 * (3.0 - dot(rot_new[:, 1], rot_new[:, 1])) * rot_new[:, 1]
    rot[:, 2] = 0.5 * (3.0 - dot(rot_new[:, 2], rot_new[:, 2])) * rot_new[:, 2]

    i = (i + 1) % 10
    if i == 0:
      acc = acc / 10.0
      xx = dot([0,0,1],rot)
      x[0:99] = x[1:100]
      y[0:99] = y[1:100]
      z[0:99] = z[1:100]
      x[99] = acc[0]
      y[99] = acc[1]
      z[99] = acc[2]
#      lx.set_ydata(x)
#      ly.set_ydata(y)
#      lz.set_ydata(z)
#      draw()
      acc = array([0,0,0])

      glMatrixMode(GL_PROJECTION)
      glLoadIdentity()
      gluPerspective(90, 1, 0.01, 1000)
      gluLookAt(-4, 0, 0, 0, 0, 0, 0, 0 ,1)
      glClearColor(0.5, 0, 0, 1)
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

      rotvect = cross(array([0.0, 0.0, 1.0]), accel / norm(accel))
      rotang = arccos(dot([0.0, 0.0, 1.0], accel) / norm(accel))
      print rotvect
      print rotang

      glMatrixMode(GL_MODELVIEW)
      glLoadIdentity()
      glRotatef(rotang*180/pi, rotvect[0], rotvect[1], rotvect[2])
      glColor3f(1,1,1,1)
      glCallList(1)
      pygame.display.flip()
    else:
      acc = acc + accel
    
finally:
  s.close()

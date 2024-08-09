void X_tfmini()
{
  while (X_DISTANCE.available() >= 9)
  {
    if ((0x59 == X_DISTANCE.read()) && (0x59 == X_DISTANCE.read()))
    {
      unsigned int t1x = X_DISTANCE.read();
      unsigned int t2x = X_DISTANCE.read();
      t2x <<= 8;
      t2x += t1x;
      x_distance = t2x ;
      t1x = X_DISTANCE.read();
      t2x = X_DISTANCE.read();
      t2x <<= 8;
      t2x += t1x;
    }
  }
}
void Y_tfmini()
{
  while (Y_DISTANCE.available() >= 9)
  {
    if ((0x59 == Y_DISTANCE.read()) && (0x59 == Y_DISTANCE.read()))
    {
      unsigned int t1y = Y_DISTANCE.read();
      unsigned int t2y = Y_DISTANCE.read();
      t2y <<= 8;
      t2y += t1y;
      y_distance = t2y ;
      t1y = Y_DISTANCE.read();
      t2y = Y_DISTANCE.read();
      t2y <<= 8;
      t2y += t1y;
    }
  }
}

void Z_tfmini()
{
  while (Z_DISTANCE.available() >= 9)
  {
    if ((0x59 == Z_DISTANCE.read()) && (0x59 == Z_DISTANCE.read()))
    {
      unsigned int t1z =  Z_DISTANCE.read();
      unsigned int t2z = Z_DISTANCE.read();
      t2z <<= 8;
      t2z += t1z;
      z_distance = t2z;
      t1z = Z_DISTANCE.read();
      t2z = Z_DISTANCE.read();
      t2z <<= 8;
      t2z += t1z;
    }
  }
}

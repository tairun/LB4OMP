#pragma once

class BaseInit {
public:
  virtual void init(int *data, int size) = 0;
  virtual void init(double *data, int size) = 0;
  virtual void init(double **data, int num_actions, int num_states) = 0;
};

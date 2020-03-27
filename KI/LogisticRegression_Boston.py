#!/usr/bin/env python
# coding: utf-8

# In[3]:


import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets
bhp = datasets.load_boston()


# In[4]:


bhp.feature_names


# In[5]:


bhp.target[0]


# In[6]:


bhp.data[0]


# In[8]:


x = bhp.data[:, 5]
y = bhp.target
plt.scatter(x,y,s=1)
plt.show()


# In[10]:


from sklearn.linear_model import LinearRegression
model =  LinearRegression().fit(bhp.data,bhp.target)


# In[25]:


x = np.linspace(0,50)
model_rooms = LinearRegression().fit(bhp.data[:,[5]],bhp.target)
predict_rooms = model_rooms.predict(bhp.data[:,[5]])
plt.scatter(bhp.target, predict_rooms, s=0.5)
plt.plot(x,x,'r')
plt.show()



# In[14]:


model_rooms.coef_, model_rooms.intercept_


# In[24]:


plt.scatter(bhp.data[:,5], bhp.target, s=1)
x = np.linspace(3,9)
plt.plot(x, model_rooms.coef_[0] * x + model_rooms.intercept_, 'r')
plt.show()




#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets
digits = datasets.load_digits()


# In[2]:


print(digits.DESCR)


# In[3]:


digits.data.shape


# In[4]:


digits.data[0]


# In[15]:


plt.imshow(digits.data[0].reshape(8,8), cmap='gray')
plt.show()


# In[19]:


from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test, = train_test_split(digits.data, digits.target)
model = LogisticRegression(solver='newton-cg', multi_class='multinomial').fit(X_train, y_train)


# In[20]:


model.score(X_test, y_test)


# In[23]:


import math

def show_digits(X, y, model, n):
    m = math.ceil(n/8)
    plt.figure(figsize=(16, 2.5*m))
    p = model.predict(X)
    for k in range(n):
        plt.subplot(m,8,k+1)
        plt.imshow(X[k].reshape(8,8), cmap='gray')
        plt.title("p: %i, a: %i" % (p[k],y[k]), color='black' if p[k] == y[k] else 'red', fontsize='16')
    plt.show()
    
show_digits(X_test, y_test, model, 50)


# In[24]:


def misclassified(X,y,model):
    pred= model.predict(X)
    Xpy = zip(X, pred, y)
    return zip(*([(X,y) for (X,p,y) in Xpy if p!= y]))

(m,l) = misclassified(X_test, y_test, model)
show_digits(m,l, model, len(l))


# In[25]:


model.decision_function(m)


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





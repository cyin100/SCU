# Conner Yin
# COEN 140 Lab 4
# 4/25/23

# Imports
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
from itertools import combinations
import math
from sklearn.metrics import mean_squared_error

# Import CA Housing Dataset
from sklearn.datasets import fetch_california_housing
hd = fetch_california_housing()
housing = pd.DataFrame(hd.data, columns=hd.feature_names)
housing['target'] = hd.target
housing.iloc[:,:].plot.scatter(x='MedInc', y='target')

def gradient(t, X, y):
    """Compute the current error and gradient."""
    # Hypothesis/estimate values for y
    y_estimate = X.dot(t).flatten()
    # Loss - the difference between the estimated and actual values of y
    loss = y.flatten() - y_estimate
    m = float(len(X))
    # Compute gradient
    grad = -(1.0 / m) * loss.dot(X)
    # Cost function value
    cost = (0.5 / m) * np.sum(np.power(loss, 2))
    return grad, cost

def gradient_descent(x, y, alpha=0.5, tolerance=1e-5, maxit=1e+6, nulbias=False):
    """ Finds the best line fit for predicting y given x. Keep track of and also 
    return tested models, gradients, and errors along the optimization path."""
    # Add intercept term to x -- acounts for the bias -- and normalize x's
    X = np.hstack((np.ones((x.shape[0], 1)), x/x.max(axis=0)))
    # Start with a random theta vector with size n+1
    t = np.random.randn(X.shape[1])
    if nulbias:
        t[0] = 0
    # perform gradient descent
    it = 0
    models = []
    grads = []
    errors = []
    while it < maxit:
        grad, error = gradient(t, X, y)
        models.append(t)
        grads.append(grad)
        errors.append(error)
        new_t = t - alpha * grad
        if nulbias:
            new_t[0] = 0
        # check whether we should stop
        if np.sum(abs(new_t - t)) < tolerance:
            break
        # update theta
        t = new_t
        it += 1
    if it == maxit:
        print("Warning: reached maximum number of iterations without convergence.")
    return X, t, models, grads, errors

def plotmodel(x, y, t, start_at_zero=False):
    """Plot the line of a given model."""
    if t is not None:
        if start_at_zero:
            x = np.append([0], x)
            y = np.append([0], y)
        plt.plot(x, t[0] + x/x.max() * t[1], c='g', label='Model')
#         equivalent to:
#         X = np.vstack((np.ones_like(x), x/x.max())).T
#         plt.plot(x, X.dot(t), c='g', label='Model')
    plt.scatter(x, y, c='b', label='Data')
    plt.legend(loc='best')
    plt.xlabel('MedInc')
    plt.ylabel('Median House Price (x$100,000)')
    if start_at_zero:
        plt.ylim(ymin=0)
        plt.xlim(xmin=0)
    plt.show()

prints = []
attributes = ['MedInc', 'HouseAge', 'AveRooms', 'AveBedrms', 'Population', 'AveOccup', 'Latitude', 'Longitude']
# Loop through every combination of 2 attributes
for attribute1, attribute2 in list(combinations(attributes, 2)):

    # Get numpy arrays for data for your 2 attributes
    data = housing.loc[:,[attribute1, attribute2, 'target']].to_numpy()
    x = data[:,0:2]
    y = data[:,2]

    # Call gradient descent with data and store values into X, t, etc.
    X, t, models, grads, errors = gradient_descent(x, y, nulbias=True) 
    
    # Store data into list and print data
    data = [attribute1, attribute2, mean_squared_error(y, X.dot(t).flatten()), y, X.dot(t).flatten()]
    prints.append(data)
    print(data)

# Sort data by mean squared error and print the lowest value
prints.sort(key=lambda x: x[2], reverse=True)
print(prints[0])





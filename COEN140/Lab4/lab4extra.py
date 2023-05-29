
prints = []
attributes = ['MedInc', 'HouseAge', 'AveRooms', 'AveBedrms', 'Population', 'AveOccup', 'Latitude', 'Longitude']
for attribute1, attribute2 in list(combinations(attributes, 2)):
    data = housing.loc[:,[attribute1, attribute2, 'target']].to_numpy()
    x = data[:,0:2]
    y = data[:,2]
    X, t, models, grads, errors = gradient_descent(x, y, nulbias=True)
    
    data = [attribute1, attribute2, mean_squared_error(y, X.dot(t).flatten()), y, X.dot(t).flatten()]
    prints.append(data)
    print(data)

prints.sort(key=lambda x: x[2], reverse=True)
print(prints[0])

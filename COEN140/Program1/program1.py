# Conner Yin
# COEN140 - Program 1
# 4/23/2023

# Imports
import numpy as np
import pandas as pd
import scipy.sparse as sp
from numpy.linalg import norm
from collections import Counter, defaultdict
from scipy.sparse import csr_matrix

# Build sparse matrix from a list of documents, 
# each of which is a list of word/terms in the document. 
def build_matrix(docs):
    nrows = len(docs)
    idx = {}
    tid = 0
    nnz = 0
    for d in docs:
        nnz += len(set(d))
        for w in d:
            if w not in idx:
                idx[w] = tid
                tid += 1
    ncols = len(idx)
        
    # set up memory
    ind = np.zeros(nnz, dtype=int)
    val = np.zeros(nnz, dtype=np.double)
    ptr = np.zeros(nrows+1, dtype=int)
    i = 0  # document ID / row counter
    n = 0  # non-zero counter
    # transfer values
    for d in docs:
        cnt = Counter(d)
        keys = list(k for k,_ in cnt.most_common())
        l = len(keys)
        for j,k in enumerate(keys):
            ind[j+n] = idx[k]
            val[j+n] = cnt[k]
        ptr[i+1] = ptr[i] + l
        n += l
        i += 1
            
    mat = csr_matrix((val, ind, ptr), shape=(nrows, ncols), dtype=np.double)
    mat.sort_indices()
    
    return mat

# Print out info about this CSR matrix. If non_empy, 
# report number of non-empty rows and cols as well
def csr_info(mat, name="", non_empy=False):
    if non_empy:
        print("%s [nrows %d (%d non-empty), ncols %d (%d non-empty), nnz %d]" % (
                name, mat.shape[0], 
                sum(1 if mat.indptr[i+1] > mat.indptr[i] else 0 
                for i in range(mat.shape[0])), 
                mat.shape[1], len(np.unique(mat.indices)), 
                len(mat.data)))
    else:
        print( "%s [nrows %d, ncols %d, nnz %d]" % (name, 
                mat.shape[0], mat.shape[1], len(mat.data)) )

# Normalize the rows of a CSR matrix by their L-2 norm. 
# If copy is True, returns a copy of the normalized matrix.
def csr_l2normalize(mat, copy=False, **kargs):
    if copy is True:
        mat = mat.copy()
    nrows = mat.shape[0]
    nnz = mat.nnz
    ind, val, ptr = mat.indices, mat.data, mat.indptr
    # normalize
    for i in range(nrows):
        rsum = 0.0    
        for j in range(ptr[i], ptr[i+1]):
            rsum += val[j]**2
        if rsum == 0.0:
            continue  # do not normalize empty rows
        rsum = 1.0/np.sqrt(rsum)
        for j in range(ptr[i], ptr[i+1]):
            val[j] *= rsum
            
    if copy is True:
        return mat

# Split the matrix and class info into train and test data using d-fold hold-out
def splitData(mat, cls, fold=1, d=10):
    n = mat.shape[0]
    r = int(np.ceil(n*1.0/d))
    mattr = []
    clstr = []
    # split mat and cls into d folds
    for f in range(d):
        if f+1 != fold:
            mattr.append( mat[f*r: min((f+1)*r, n)] )
            clstr.extend( cls[f*r: min((f+1)*r, n)] )
    # join all fold matrices that are not the test matrix
    train = sp.vstack(mattr, format='csr')
    # extract the test matrix and class values associated with the test rows
    test = mat[(fold-1)*r: min(fold*r, n), :]
    clste = cls[(fold-1)*r: min(fold*r, n)]

    return train, clstr, test, clste
    
# x is one row in test occurences
def classify(x, train, clstr, k=6):
    r""" Classify vector x using kNN and majority vote rule given training data and associated classes
    """
    # find nearest neighbors for x
    dots = x.dot(train.T)
    sims = list(zip(dots.indices, dots.data))
    if len(sims) == 0:
        # could not find any neighbors
        return '+' if np.random.rand() > 0.5 else '-'
    sims.sort(key=lambda x: x[1], reverse=True)
    tc = Counter(clstr[s[0]] for s in sims[:k]).most_common(2)
    if len(tc) < 2 or tc[0][1] > tc[1][1]:
        # majority vote
        return tc[0][0]
    # tie break
    tc = defaultdict(float)
    for s in sims[:k]:
        tc[clstr[s[0]]] += s[1]
    return sorted(tc.items(), key=lambda x: x[1], reverse=True)[0][0]
        
    macc = 0.0
    for f in range(d):
        # split data into training and testing
        train, clstr, test, clste = splitData(mat, cls, f+1, d)
        # predict the class of each test sample
        clspr = [ classify(test[i,:], train, clstr) for i in range(test.shape[0]) ]
        # compute the accuracy of the prediction
        acc = 0.0
        for i in range(len(clste)):
            if clste[i] == clspr[i]:
                acc += 1
        acc /= len(clste)
        macc += acc
        
    return macc/d

# Importing data
names, cls = [], []
trainData = open('train.dat').readlines()
for line in trainData:
    names.append(line[2:].strip())
    cls.append(line[0])
testData = open('test.dat').readlines()
fullData = names + testData

# Combine data into matrix
full_matrix = build_matrix(fullData)
csr_l2normalize(full_matrix)
train_csr = full_matrix[:len(names)]
test_csr = full_matrix[len(names):]
csr_info(train_csr)
csr_info(test_csr)

# Print classifications to output.txt
with open('prediction.txt', 'w') as f:
    for i in range(test_csr.shape[0]):
        guess = classify(test_csr[i], train_csr, cls, 6)
        print(i, end='\r') # For debugging/tracking progress
        f.write(f"{guess}\n")
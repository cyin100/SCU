Object subclass: #Node
    instanceVariableNames: 'data link'
    classVariableNames: ''
    poolDictionaries: ''
    category: 'examples'!



!Node class methodsFor: 'instance creation'!
data: anObject
    "Note that 'Node new' will answer a new node object with data and link
     both initialized to nil, which for this class seems appropriate.  This
     class method conveniently lets us create the node and initialize the
     data at the same time.  Note that we invoke the mutator."

    ^(self new) initialize: anObject
!!


!Node methodsFor: 'access'!
data					"data accessor"
    ^data
!

link					"link accessor"
    ^link
!

initialize: anObject			"data mutator (answer self)"
    data := anObject
!

linkTo: aNode				"link mutator (answer self)"
    link := aNode
!!
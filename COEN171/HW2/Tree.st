"Conner Yin"

Object subclass: #Node
    instanceVariableNames: 'data left right'
    classVariableNames: ''
    poolDictionaries: ''!

!Node class methodsFor: 'creation'!
data: anObject
    ^self new initialize: anObject
!!

!Node methodsFor: 'access'!

initialize: anObject
    data := anObject
!

insert: anObject
    anObject < data
        ifTrue: [left isNil
            ifTrue: [left := Node data: anObject]
            ifFalse: [left insert: anObject]
        ]
        ifFalse: [right isNil
            ifTrue: [right := Node data: anObject]
            ifFalse: [right insert: anObject]
        ]
!

member: anObject
    |result|
    anObject = data
        ifTrue: [result := True]
        ifFalse: [
            anObject < data
                ifTrue: [left isNil
                    ifTrue: [result := false]
                    ifFalse: [result := left member: anObject]
                ]
                ifFalse: [right isNil
                    ifTrue: [result := false]
                    ifFalse: [result := right member: anObject]
                ]
        ].
    ^result
!!

Object subclass: #Tree
    instanceVariableNames: 'root'
    classVariableNames: ''
    poolDictionaries: ''!

!Tree class methodsFor: 'creation'!
new
    ^super new initialize
!!

!Tree methodsFor: 'initialization'!

initialize
    root := nil
!

insert: anObject
    root isNil
        ifTrue: [root := Node data: anObject]
        ifFalse: [root insert: anObject]
!

member: anObject
    |result|
    root isNil
        ifTrue: [result := false]
        ifFalse: [result := root member: anObject].
    ^result
!!
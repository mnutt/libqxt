/*******************************************************************
Qt extended Library 
Copyright (C) 2007 Adam Higerd
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/
/**
\class QxtPimpl QxtPimpl
\ingroup core
\brief hide implementaion with PIMPL
 
Application code generally doesn't have to be concerned about hiding its implementation details, but when writing library code it is important to maintain a constant interface, both source and binary. Maintaining a constant source interface is easy enough, but keeping the binary interface constant means moving implementation details into a private class. The PIMPL, or d-pointer, idiom is a common method of implementing this separation. QxtPimpl offers a convenient way to connect the public and private sides of your class. (header, example)

\section start Getting Started 
Before you declare the public class, you need to make a forward declaration of the private class. The private class must have the same name as the public class, followed by the word Private. In the example above, the class is named MyTest so the private class is declared with: 
class MyTestPrivate;

\subsection pub The Public Class 
Generally, you shouldn't keep any data members in the public class without a good reason. (The example above keeps a data member in the public class only for the sake of demonstration.) Functions that are part of the public interface should be declared in the public class, and functions that need to be available to subclasses (for calling or overriding) should be in the protected section of the public class. 
To connect the private class to the public class, include the QXT_DECLARE_PRIVATE macro in the private section of the public class. In the example above, the private class is connected as follows: 
private:
    QXT_DECLARE_PRIVATE(MyTest);
Furthermore, if the private class needs to access the public class, include the QXT_INIT_PRIVATE macro in the public class's constructor. The example looks like this: 

\code
MyTest::MyTest() {
    // initialization
    QXT_INIT_PRIVATE(MyTest);
}
\endcode

\subsection priv The Private Class 
As mentioned above, data members should usually be kept in the private class. This allows the memory layout of the private class to change without breaking binary compatibility for the public class. Functions that exist only as implementation details, or functions that need access to private data members, should be implemented here. 
To allow the private class to access members of the public class, include the QXT_DECLARE_PUBLIC macro in the public section of the private class. Additionally, the private class needs to inherit some functionality from QxtPrivate. QxtPrivate is a template class, so your private class declaration should look something like this excerpt from the example: 
\code
class MyTestPrivate : public QxtPrivate<MyTest> {
public:
    MyTestPrivate();
    QXT_DECLARE_PUBLIC(MyTest);

    // rest of class declaration
};
\endcode
This is technically optional -- if your private class has no need to access the public class members at all, then the superclass inheritance, QXT_DECLARE_PUBLIC, and QXT_INIT_PRIVATE in the public class's constructor can be omitted. The qxt_p() function described below will be unavailable if you decide to do this. 
[edit]
\section cross Crossing the Boundary 
Once the two classes are declared and connected, functions in the public class can use the qxt_d() function (actually a function-like object), which returns a reference to the private object. 
Similarly, should the private class wish to access the public class (for instance, to call a virtual function that might be overridden by a subclass), the qxt_p() function (this one's really a function) returns a reference back to the public object. 
[edit]
\section about  About the Example 
The example program demonstrates the use of QxtPimpl. It also demonstrates how a subclass can have its own independent private class without disturbing the superclass. The use of virtual functions is left as an exercise to the reader; a search of the Internet will provide further information about the PIMPL idiom.
*/




#ifndef QXTPIMPL_H
#define QXTPIMPL_H

#define QXT_DECLARE_PRIVATE(C) friend class C##Private; QxtPrivateInterface<C, C##Private> qxt_d;
#define QXT_DECLARE_PUBLIC(C) friend class C;
#define QXT_INIT_PRIVATE(C) qxt_d.setPublic(this);

template <typename PUB, typename PVT>
class QxtPrivateInterface {
public:
    inline QxtPrivateInterface() { pvt = new PVT; }
    inline ~QxtPrivateInterface() { delete pvt; }

    inline void setPublic(PUB* pub) { pvt->QXT_setPublic(pub); }
    inline PVT& operator()() { return *pvt; }

private:
    PVT* pvt;
};

template <typename PUB>
class QxtPrivate {
public:
    inline void QXT_setPublic(PUB* pub) { qxt_p_ptr = pub; }

protected:
    inline PUB& qxt_p() { return *qxt_p_ptr; }

private:
    PUB* qxt_p_ptr;
};

#endif

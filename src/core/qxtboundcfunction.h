
template <typename FUNCTION, int argc, typename RETURN>
class QxtBoundCFunction : public QxtBoundFunctionBase {
public:
    FUNCTION funcPtr;

    QxtBoundCFunction(QObject* parent, FUNCTION funcPointer, QGenericArgument* params[argc], QByteArray types[argc]) : QxtBoundFunctionBase(parent, params, types), funcPtr(funcPointer) {
        // initializers only, thanks to template magic
    }

    virtual bool invokeImpl(Qt::ConnectionType type, QGenericReturnArgument returnValue, QXT_IMPL_10ARGS(QGenericArgument)) {
        return qxt_invoke_cfunction_return<FUNCTION, argc, RETURN>(funcPtr, returnValue, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
    }
};

template <typename FUNCTION, int argc>
class QxtBoundCFunction<FUNCTION, argc, void> : public QxtBoundFunctionBase {
public:
    FUNCTION funcPtr;

    QxtBoundCFunction(QObject* parent, FUNCTION funcPointer, QGenericArgument* params[argc], QByteArray types[argc]) : QxtBoundFunctionBase(parent, params, types), funcPtr(funcPointer) {
        // initializers only, thanks to template magic
    }

    virtual bool invokeImpl(Qt::ConnectionType type, QGenericReturnArgument returnValue, QXT_IMPL_10ARGS(QGenericArgument)) {
        return qxt_invoke_cfunction<FUNCTION, argc>(funcPtr, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
    }
};

QGenericArgument* qbcfP[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
QByteArray types[10] = { "", "", "", "", "", "", "", "", "", "" };

void testFunction(int a) { a++; return; }
template < typename FP > QxtBoundFunction* testBind(FP fn) { return new QxtBoundCFunction<FP, 1>(0, fn, qbcfP, types); }
QxtBoundCFunction<void(*)(int), 1> qbcf(0, testFunction, qbcfP, types);
QxtBoundFunction* qbf = testBind(testFunction);



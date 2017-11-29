/* visitable.h */
/* Visitable Interface */

#define DEFINE_VISITABLE() \
	virtual ReturnType Accept(AcyclicVisitor& guest) \
		override { \
		return this->AcceptImpl(*this, guest); \
	}


template <typename R = void>
class Visitable {
public:
	using ReturnType = R;
	virtual ~Visitable() {}
	virtual R Accept(AcyclicVisitor&) = 0;

protected:
	template <class T>
	static R AcceptImpl(T& v, AcyclicVisitor& g)
	{
		assert(typeid(v) == typeid(T)
			&& "Please use DEFINE_VISITABLE");
		// Apply Acyclic Visitor
		if (auto p = dynamic_cast<Visitor<T, R>*>(&g)) {
			return p->Visit(v);
		}
		return R();
	}
}






#ifndef ADJOINT_CORE_UTILITY_HPP_
#define ADJOINT_CORE_UTILITY_HPP_


namespace adjoint
{

class Context;

class Contextualized
{
public:
    Contextualized( adjoint::Context* context );

protected:
    adjoint::Context* m_context;
};


inline Contextualized::Contextualized( adjoint::Context* context )
    : m_context( context )
{
}


} // namespace adjoint


#endif // ADJOINT_CORE_UTILITY_HPP_

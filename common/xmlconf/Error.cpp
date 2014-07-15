#include <Error.h>

NS_VITO_XML_CONF

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

CError::CError(const string& rcsDesc) throw() : std::runtime_error(rcsDesc)
{
}

CError::~CError() throw()
{
}

NS_END_LAYER_3

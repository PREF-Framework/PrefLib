#ifndef PREFLIB_FORMAT_FIELD_H
#define PREFLIB_FORMAT_FIELD_H

#include "fieldelement.h"
#include "bitfield.h"

namespace PrefLib {
namespace Format {

using namespace Core;

class Field: public FieldElement
{
    public:
        Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, lua_State* thread);
        Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, DataValue& valid, lua_State* thread);
        Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, LuaTable& valid, lua_State* thread);
        ~Field();

    public:
        virtual DataValue value();
        BitField* bitField(int i) const;
        BitField* bitField(const char* name) const;
        BitField* setBitField(const char* name, uint64_t bitstart, uint64_t bitend);
        BitField* setBitField(const char* name, uint64_t bitstart);

    lua_api:
        static int luaSetBitField(lua_State*l);

    protected:
        virtual FormatElement::Type type() const;
};

} // namespace Format
} // namespace PrefLib

#endif // PREFLIB_FORMAT_FIELD_H

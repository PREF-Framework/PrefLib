#include "disassemblercontext.h"

namespace PrefLib {
namespace Disassembler {

DisassemblerContext::DisassemblerContext()
{
    this->push();
    this->setFunction("create", &DisassemblerContext::luaCreate);
    lua_pop(LuaState::instance(), 1);
}

DisassemblerContext::~DisassemblerContext()
{

}

void DisassemblerContext::push() const
{
    lua_State* l = LuaState::instance();
    LuaTable::push();

    lua_newtable(l);

    lua_pushinteger(l, Segment::Code);
    lua_setfield(l, -2, "Code");

    lua_pushinteger(l, Segment::Data);
    lua_setfield(l, -2, "Data");

    lua_setfield(l, -2, "segmenttype");
}

DisassemblerDefinition *DisassemblerContext::get(int idx) const
{
    lua_State* l = LuaState::instance();
    DisassemblerDefinition* disassemblerdefinition = nullptr;

    this->push();
    lua_rawgeti(l, -1, idx + 1);

    if(!lua_isnoneornil(l, -1))
        disassemblerdefinition = reinterpret_cast<DisassemblerDefinition*>(checkThis(l, -1));

    lua_pop(l, 2);
    return disassemblerdefinition;
}

int DisassemblerContext::luaCreate(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 6);

    DisassemblerContext* thethis = reinterpret_cast<DisassemblerContext*>(checkThis(l, 1));

    DisassemblerDefinition* dd = new DisassemblerDefinition(luaL_checkstring(l, 2), reinterpret_cast<Format::FormatDefinition*>(checkThis(l, 3)),
                                                            static_cast<DataType::Type>(luaL_checkinteger(l, 4)), luaL_checkstring(l, 5), luaL_checkstring(l, 6));

    thethis->bindTable(dd->name(), dd);
    dd->push();
    return 1;
}

} // namespace Disassembler
} // namespace PrefLib

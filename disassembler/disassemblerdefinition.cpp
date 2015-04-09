#include "disassemblerdefinition.h"

namespace PrefLib {
namespace Disassembler {

DisassemblerDefinition::DisassemblerDefinition(const char* name, Format::FormatDefinition* formatdefinition, DataType::Type addresstype, const char* author, const char* version): LuaTable()
{
    lua_State* l = LuaState::instance();

    this->push();
    this->setString("name", name);
    this->setTable("format", formatdefinition);
    this->setInteger("addresstype", addresstype);
    this->setString("author", author);
    this->setString("version", version);
    lua_pop(l, 1);
}

DisassemblerDefinition::~DisassemblerDefinition()
{

}

void DisassemblerDefinition::initialize()
{
    if(!this->hasField("initialize"))
        return;

    lua_State* l = LuaState::instance();

    this->push();
    lua_getfield(l, -1, "initialize");
    this->push(); // Self
    this->protectedCall(1, 0);
    lua_pop(l, 1);
}

void DisassemblerDefinition::finalize()
{
    if(!this->hasField("finalize"))
        return;

    lua_State* l = LuaState::instance();

    this->push();
    lua_getfield(l, -1, "finalize");
    this->push(); // Self
    this->protectedCall(1, 0);
    lua_pop(l, 1);
}

void DisassemblerDefinition::map(DisassemblerListing *listing)
{
    if(!this->hasField("map"))
        return;

    lua_State* l = LuaState::instance();

    this->push();
    lua_getfield(l, -1, "map");
    this->push(); // Self
    listing->push();
    this->protectedCall(2, 0);
    lua_pop(l, 1);
}

void DisassemblerDefinition::disassemble(DisassemblerListing* listing, DataValue &address)
{
    if(!this->hasField("disassemble"))
        return;

    lua_State* l = LuaState::instance();
    address.castTo(this->addressType());

    this->push();
    lua_getfield(l, -1, "disassemble");
    this->push(); // Self
    listing->push();
    address.push();
    this->protectedCall(3, 0);
    lua_pop(l, 1);
}

const char* DisassemblerDefinition::name() const
{
    return this->getString("name");
}

const char* DisassemblerDefinition::author() const
{
    return this->getString("author");
}

const char* DisassemblerDefinition::version() const
{
    return this->getString("version");
}

const Format::FormatDefinition *DisassemblerDefinition::format() const
{
    return dynamic_cast<Format::FormatDefinition*>(this->getTable("format"));
}

DataType::Type DisassemblerDefinition::addressType() const
{
    return static_cast<DataType::Type>(this->getInteger("addresstype"));
}

int DisassemblerDefinition::luaNext(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 2);

    int t = lua_type(l, 2);

    if(t == LUA_TTABLE) /* Custom Instruction */
    {
        Block* b = reinterpret_cast<Block*>(checkThis(l, 2));
        lua_pushinteger(l, b->size());
        return 1;
    }

    cs_insn* insn = (*(cs_insn**)luaL_checkudata(l, 1, "__insn"));
    lua_pushinteger(l, insn->size);
    return 1;
}

} // namespace Disassembler
} // namespace PrefLib


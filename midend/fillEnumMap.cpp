#include "fillEnumMap.h"
#include "frontends/p4/enumInstance.h"

namespace P4 {

const IR::Node* FillEnumMap::preorder(IR::Type_Enum* type) {
    if (strstr(type->srcInfo.filename, "v1model") == nullptr) {
        unsigned long long count = type->members.size();
        unsigned long long width = policy->enumSize(count);
        auto r = new EnumRepresentation(type->srcInfo, width);
        auto canontype = typeMap->getTypeType(getOriginal(), true);
        BUG_CHECK(canontype->is<IR::Type_Enum>(),
                  "canon type of enum %s is non enum %s?", type, canontype);
        repr.emplace(canontype->to<IR::Type_Enum>(), r);
        for (auto d : type->members)
            r->add(d->name.name);
    }
    return type;
}

}  // namespace P4

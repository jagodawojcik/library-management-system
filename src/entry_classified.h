#pragma once

#include <string>

#include "entry.h"

struct EntryClassified
{
    std::string entryType;
    std::shared_ptr<Entry> pEntry;
};

#include "pch.h"
#include "EnginePch.h"

#include "Engine.h"

unique_ptr<Engine> g_engine = make_unique<Engine>();

Engine& GEngine()
{
    return *(g_engine.get());
}

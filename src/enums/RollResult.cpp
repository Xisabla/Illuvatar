#include "enums/RollResult.h"

using namespace std;

ostream& operator<<(ostream& out, const RollResult value) {
    const char* s = nullptr;
#define PROCESS_VAL(p) case(p): s = #p; break;
    switch(value){
        PROCESS_VAL(RollResult::CriticalSuccess)
        PROCESS_VAL(RollResult::Success)
        PROCESS_VAL(RollResult::Failure)
        PROCESS_VAL(RollResult::CriticalFailure)
    }
#undef PROCESS_VAL

    return out << s;
}

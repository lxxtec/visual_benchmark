#include <iostream>
#include "benchmark.h"

namespace BenchMark {
void Function1(void) {
    // InstrumentationTimer timer("fun1");
    PROFILE_FUNCTION();
    int temp;
    for (int i = 0; i < 2000000; i++) {
        temp = i * i * i;
    }
}

void Function2(int a = 0) {
    PROFILE_FUNCTION();
    int temp;
    for (int i = 0; i < 2000000; i++) {
        temp = i * i * i;
    }
}

void RunBenchMark() {
    // PROFILE_FUNCTION();
    std::cout << "Starting benchmark" << std::endl;
    Function1();
    Function2();
    std::thread a([]() { Function1(); });
    std::thread b([]() { Function2(); });
    a.join();
    b.join();
}
}  // namespace BenchMark

int main() {
    Instrumentor::Get().BeginSession("Profile");
    BenchMark::RunBenchMark();
    Instrumentor::Get().EndSession();
}
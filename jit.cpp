#include <iostream>
#include <cstring>
#include <sys/mman.h>

const size_t funcSize = 55;
const uint64_t initialPos = 7;
const uint64_t deducePos = 14;
const uint8_t func[] = {
    0x55,                  	                    
    0x48, 0x89, 0xe5,             	            
    0xc7, 0x45, 0xf8, 0x2a, 0x00, 0x00, 0x00, 	
    0xc7, 0x45, 0xfc, 0x54, 0x00, 0x00, 0x00, 	
    0x8b, 0x45, 0xf8,             	            
    0x3b, 0x45, 0xfc,             	            
    0x7e, 0x07,           	                    
    0xb8, 0x01, 0x00, 0x00, 0x00,       	    
    0xeb, 0x14,                                 
    0x8b, 0x45, 0xf8,             	            
    0x3b, 0x45, 0xfc,             	            
    0x7d, 0x07,                	                
    0xb8, 0x02, 0x00, 0x00, 0x00,      	          
    0xeb, 0x05,                	                  
    0xb8, 0x00, 0x00, 0x00, 0x00,       	        
    0x5d,                  	                           
    0xc3                   	                            
};

/*
push   %rbp
mov    %rsp,%rbp
movl   $0x2a,-0x8(%rbp)
movl   $0x54,-0x4(%rbp)
mov    -0x8(%rbp),%eax
cmp    -0x4(%rbp),%eax
jle    113a <_Z4funcv+0x21>
mov    $0x1,%eax
jmp    114e <_Z4funcv+0x35>
mov    -0x8(%rbp),%eax
cmp    -0x4(%rbp),%eax
jge    1149 <_Z4funcv+0x30>
mov    $0x2,%eax
jmp    114e <_Z4funcv+0x35>
mov    $0x0,%eax
pop    %rbp
retq   
*/

int main() {
    srand(time(0));
    int numberToDeduce = rand() % 100 + 1;
    void *addr = mmap(NULL, funcSize, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    std::memcpy(addr, func, funcSize);
    int (*fcnPtr)() = reinterpret_cast<int(*)()>(addr);
    std::memcpy(addr + initialPos, &numberToDeduce, 4);
    while (true) {
        uint64_t a;
        std::cin >> a;
        std::memcpy(addr + deducePos, &a, 4);
        int result = fcnPtr();
        if (result == 1) {
            printf("Smaller then mine\n");
        } else if (result == 2) {
            printf("Greater then mine\n");
        } else {
            printf("Correct\n");
            break;
        }
    }
}

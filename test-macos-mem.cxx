#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/sysctl.h>
/*
int main(void)
{
    int mib[2] = { CTL_HW, HW_MEMSIZE };
    u_int namelen = sizeof(mib) / sizeof(mib[0]);
    uint64_t size;
    size_t len = sizeof(size);

    if (sysctl(mib, namelen, &size, &len, NULL, 0) < 0)
    {
        perror("sysctl");
    }
    else
    {
        printf("HW.HW_MEMSIZE = %llu bytes\n", size);
    }

    printf("Free memory       : %ld\n", vmt.t_free * (u_int64_t)page_size);
    printf("Available memory  : %ld\n", vmt.t_avm * (u_int64_t)page_size);

    return 0;
}
*/

#include <stdio.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/vmmeter.h>

int main(){
    int rc;
    u_int page_size;
    struct vmtotal vmt;
    size_t vmt_size, uint_size; 

    vmt_size = sizeof(vmt);
    uint_size = sizeof(page_size);

    rc = sysctl("vm.vmtotal", &vmt, &vmt_size, NULL, 0);
    if (rc < 0){
       perror("sysctl");
       return 1;
    }

    rc = sysctl("vm.stats.vm.v_page_size", &page_size, &uint_size, NULL, 0);
    if (rc < 0){
       perror("sysctl");
       return 1;
    }

    printf("Free memory       : %ld\n", vmt.t_free * (u_int64_t)page_size);
    printf("Available memory  : %ld\n", vmt.t_avm * (u_int64_t)page_size);

    return 0;
}

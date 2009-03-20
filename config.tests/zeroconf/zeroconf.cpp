#include <dns_sd.h>

int main(int, char**) {
    char buffer[kDNSServiceMaxDomainName];
    return DNSServiceConstructFullName(buffer, 0, "_foo._tcp", "domain");
}

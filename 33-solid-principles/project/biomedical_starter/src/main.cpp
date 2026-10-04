#include "ward_manager.h"

int main() {
    WardManager ward;
    ward.wardName = "Medical Ward A";
    ward.admit("Bed 1", "Esi Badu");
    ward.admit("Bed 2", "Yaw Darko");
    ward.admit("Bed 3", "Akosua Frimpong");

    ward.record("Bed 1", "hr", 78);
    ward.record("Bed 1", "temp", 36.8);
    ward.record("Bed 1", "spo2", 98);
    ward.record("Bed 1", "sbp", 124);

    ward.record("Bed 2", "hr", 118);
    ward.record("Bed 2", "temp", 39.4);
    ward.record("Bed 2", "spo2", 92);
    ward.record("Bed 2", "sbp", 98);

    ward.record("Bed 3", "hr", 96);
    ward.record("Bed 3", "temp", 37.2);
    ward.record("Bed 3", "spo2", 90);
    ward.record("Bed 3", "sbp", 132);

    ward.doShift();
    return 0;
}

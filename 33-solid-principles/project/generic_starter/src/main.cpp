#include "school_manager.h"

int main() {
    SchoolManager school;
    school.addStudent("MP-001", "Ama Mensah", "0244000001", "none");
    school.addStudent("MP-002", "Kojo Asante", "0244000002", "academic");
    school.addStudent("MP-003", "Esi Quaye", "0244000003", "sports");
    school.addStudent("MP-004", "Yaw Boateng", "0244000004", "none");

    school.addResult("MP-001", "exam", 92, 100);
    school.addResult("MP-001", "test", 46, 50);
    school.addResult("MP-001", "homework", 19, 20);
    school.addResult("MP-002", "exam", 71, 100);
    school.addResult("MP-002", "homework", 15, 20);
    school.addResult("MP-003", "exam", 48, 100);
    school.addResult("MP-003", "test", 22, 50);
    school.addResult("MP-004", "exam", 58, 100);
    school.addResult("MP-004", "test", 35, 50);

    school.doEverything();
    return 0;
}

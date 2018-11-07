#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\6.1.7600.17795\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_7600
{

    typedef union _KWAIT_STATUS_REGISTER
    {
        union
        {
            UINT8 Flags;
            struct /* bitfield */
            {
                UINT8 State : 2; /* bit position: 0 */
                UINT8 Affinity : 1; /* bit position: 2 */
                UINT8 Priority : 1; /* bit position: 3 */
                UINT8 Apc : 1; /* bit position: 4 */
                UINT8 UserApc : 1; /* bit position: 5 */
                UINT8 Alert : 1; /* bit position: 6 */
                UINT8 Unused : 1; /* bit position: 7 */
            }; /* bitfield */
        }; /* size: 0x0001 */
    } KWAIT_STATUS_REGISTER, *PKWAIT_STATUS_REGISTER; /* size: 0x0001 */
    static_assert(sizeof(KWAIT_STATUS_REGISTER) == 0x0001);


}

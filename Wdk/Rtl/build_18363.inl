#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\10.0.18362.1\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_18363
{

    SameDefine$(build_18362, RTL_BALANCED_NODE);
    SameDefine$(build_18362, RTL_AVL_TREE);

    typedef struct _RTL_RB_TREE
    {
        struct _RTL_BALANCED_NODE* Root;
        union
        {
            UINT8 Encoded : 1; /* bit position: 0 */
            struct _RTL_BALANCED_NODE* Min;
        };
    } RTL_RB_TREE, * PRTL_RB_TREE; /* size: 0x0010 */  /* size: 0x0008 */

}

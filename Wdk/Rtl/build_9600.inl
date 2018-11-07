#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\6.3.9600.19038\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_9600
{

    typedef struct _RTL_BALANCED_NODE
    {
        union
        {
            struct _RTL_BALANCED_NODE* Children[2];
            struct
            {
                struct _RTL_BALANCED_NODE* Left;
                struct _RTL_BALANCED_NODE* Right;
            }; /* size: 0x0010 */ /* size: 0x0008 */
        }; /* size: 0x0010 */ /* size: 0x0008 */
        union
        {
            UINT8 Red : 1; /* bit position: 0 */
            UINT8 Balance : 2; /* bit position: 0 */
            SIZE_T ParentValue;
        }; /* size: 0x0008 */ /* size: 0x0004 */
    } RTL_BALANCED_NODE, *PRTL_BALANCED_NODE; /* size: 0x0018 */ /* size: 0x000c */
    static_assert(sizeof(RTL_BALANCED_NODE) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0018 : 0x000c));


    typedef struct _RTL_RB_TREE
    {
        struct _RTL_BALANCED_NODE* Root;
        struct _RTL_BALANCED_NODE* Min;
    } RTL_RB_TREE, *PRTL_RB_TREE; /* size: 0x0010 */  /* size: 0x0008 */


    typedef struct _RTL_AVL_TREE
    {
        struct _RTL_BALANCED_NODE* Root;
    } RTL_AVL_TREE, *PRTL_AVL_TREE;


}

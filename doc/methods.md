# Method Definitions and Indexes #

Attempt to list all methods and indexes from the LB4OMP runtime.

## Start of kmp_dispatch.cpp ##

```cpp
// LB4OMP extended DLS portfolio ...scheduling techniques are ordered according to their overhead/scheduling/load balancing capacity
std::vector<sched_type> autoDLSPortfolio{
        kmp_sch_static_chunked,             // STATIC ... 0
        kmp_sch_dynamic_chunked,            // ... 1
        kmp_sch_trapezoidal,                // TSS ... 2
        kmp_sch_guided_analytical_chunked,  // ... 3 LLVM RTL original auto, which is guided with minimum chunk size
        kmp_sch_guided_iterative_chunked,   // ... 4 GSS
        //--------------LB4OMP_extensions----------
        //kmp_sch_fsc,                      // requires profiling
        //kmp_sch_tap,                      // requires profiling
        //kmp_sch_fac,                      // requires profiling
        //kmp_sch_faca,                     // requires profiling
        kmp_sch_fac2a,                      // ... 5
        // kmp_sch_fac2,                    // fac2a is more optimized implementation
        kmp_sch_static_steal,               // ... 6 static_steal
        //kmp_sch_wf,                       // not needed on homogeneous cores
        //kmp_sch_bold,                     // requires profiling
        kmp_sch_awf_b,                      // ... 7
        kmp_sch_awf_c,                      // ... 8
        kmp_sch_awf_d,                      // ... 9
        kmp_sch_awf_e,                      // ... 10
        kmp_sch_af_a,                       // ... 11
        //kmp_sch_af,                       //  af_a is more optimized implementation
};

enum DLSPortfolio {
    STATIC, SS, TSS, GSS_LLVM, GSS, mFAC2, static_steal, AWFB, AWFC, AWFD, AWFE, mAF
};
```

## void print_loop_timer(enum sched_type schedule, int tid_for_timer, int nThreads) ##

```cpp
    std::string DLS[70];
    DLS[33] = "STATIC";
    DLS[34] = "static unspecialized";
    DLS[35] = "SS";
    DLS[39] = "TSS";
    DLS[40] = "static_greedy";
    DLS[41] = "static_balanced";
    DLS[42] = "GSS";
    DLS[43] = "Auto(LLVM)";
    DLS[44] = "Static Steal";
    DLS[45] = "static_balanced_chunked";
    DLS[46] = "kmp_sch_guided_simd";
    //--------------LB4OMP_extensions----------------
    DLS[48] = "FSC";
    DLS[49] = "TAP";
    DLS[50] = "FAC";
    DLS[51] = "mFAC";
    DLS[52] = "FAC2";
    DLS[53] = "mFac2";
    DLS[54] = "WF";
    DLS[55] = "BOLD";
    DLS[56] = "AWF-B";
    DLS[57] = "AWF-C";
    DLS[58] = "AWF-D";
    DLS[59] = "AWF-E";
    DLS[60] = "AF";
    DLS[61] = "mAF";
    DLS[62] = "Profiling";
    DLS[63] = "AWF";
```

## kmp.h ##

```cpp
typedef enum kmp_sched {
  kmp_sched_lower = 0, // lower and upper bounds are for routine parameter check
  // Note: need to adjust __kmp_sch_map global array in case enum is changed
  kmp_sched_static = 1, // mapped to kmp_sch_static_chunked           (33)
  kmp_sched_dynamic = 2, // mapped to kmp_sch_dynamic_chunked          (35)
  kmp_sched_guided = 3, // mapped to kmp_sch_guided_chunked           (36)
  kmp_sched_auto = 4, // mapped to kmp_sch_auto                     (38)
  kmp_sched_upper_std = 5, // upper bound for standard schedules
  kmp_sched_lower_ext = 100, // lower bound of Intel extension schedules
  kmp_sched_trapezoidal = 101, // mapped to kmp_sch_trapezoidal (39)
#if KMP_STATIC_STEAL_ENABLED
  kmp_sched_static_steal = 102, // mapped to kmp_sch_static_steal (44)
#endif
  //--------------LB4OMP_extensions----------------
  kmp_sched_fsc = 103, // mapped to kmp_sch_fsc (48)
  kmp_sched_tap = 104, // mapped to kmp_sch_tap (49)
  kmp_sched_fac = 105, // mapped to kmp_sch_fac (50)
  kmp_sched_faca = 106, // mapped to kmp_sch_faca (51)
  kmp_sched_fac2 = 107, // mapped to kmp_sch_fac2 (52)
  kmp_sched_fac2a = 108, // mapped to kmp_sch_fac2a (53)
  kmp_sched_wf = 109, // mapped to kmp_sch_wf (54)
  kmp_sched_bold = 110, // mapped to kmp_sch_bold (55)
  kmp_sched_awf_b = 111, // mapped to kmp_sch_awf_b (56)
  kmp_sched_awf_c = 112, // mapped to kmp_sch_awf_c (57)
  kmp_sched_awf_d = 113, // mapped to kmp_sch_awf_d (58)
  kmp_sched_awf_e = 114, // mapped to kmp_sch_awf_e (59)
  kmp_sched_af = 115, // mapped to kmp_sch_af (60)
  kmp_sched_af_a = 116, // mapped to kmp_sch_af_a (61)
  kmp_sched_profiling = 117, // mapped to kmp_sch_profiling (62)
  kmp_sched_awf = 118, // mapped to kmp_sch_awf (63)
  kmp_sched_pls=119, // mapped to kmp_sch_pls (72)
  kmp_sched_tfss = 120, //map kmp_sch_tfss (73)
  kmp_sched_mfsc = 121, //map kmp_sch_mfsc (74)
  kmp_sched_fiss = 122, //map kmp_sch_fiss (75)
  kmp_sched_viss = 123, //map kmp_sch_viss (76)
  kmp_sched_rnd = 124, //map kmp_sch_rnd (77)
  kmp_sched_fac2b = 125, //map kmp_sch_fac2b (78)
  //--------------LB4OMP_extensions----------------
  kmp_sched_upper,
  kmp_sched_default = kmp_sched_static // default scheduling
} kmp_sched_t;
#endif

/*!
 @ingroup WORK_SHARING
 * Describes the loop schedule to be used for a parallel for loop.
 */
enum sched_type : kmp_int32 {
  kmp_sch_lower = 32, /**< lower bound for unordered values */
  kmp_sch_static_chunked = 33,
  kmp_sch_static = 34, /**< static unspecialized */
  kmp_sch_dynamic_chunked = 35,
  kmp_sch_guided_chunked = 36, /**< guided unspecialized */
  kmp_sch_runtime = 37,
  kmp_sch_auto = 38, /**< auto */
  kmp_sch_trapezoidal = 39,

  /* accessible only through KMP_SCHEDULE environment variable */
  kmp_sch_static_greedy = 40,
  kmp_sch_static_balanced = 41,
  /* accessible only through KMP_SCHEDULE environment variable */
  kmp_sch_guided_iterative_chunked = 42,
  kmp_sch_guided_analytical_chunked = 43,
  /* accessible only through KMP_SCHEDULE environment variable */
  kmp_sch_static_steal = 44,

#if OMP_45_ENABLED
  /* static with chunk adjustment (e.g., simd) */
  kmp_sch_static_balanced_chunked = 45,
  kmp_sch_guided_simd = 46, /**< guided with chunk adjustment */
  kmp_sch_runtime_simd = 47, /**< runtime with chunk adjustment */
#endif

  //--------------LB4OMP_extensions----------------
  kmp_sch_fsc = 48,
  kmp_sch_tap = 49,
  kmp_sch_fac = 50,
  kmp_sch_faca = 51,
  kmp_sch_fac2 = 52,
  kmp_sch_fac2a = 53,
  kmp_sch_wf = 54,
  kmp_sch_bold = 55,
  kmp_sch_awf_b = 56,
  kmp_sch_awf_c = 57,
  kmp_sch_awf_d = 58,
  kmp_sch_awf_e = 59,
  kmp_sch_af = 60,
  kmp_sch_af_a = 61,
  kmp_sch_profiling = 62,
  kmp_sch_awf = 63,
  kmp_sch_pls=72,
  kmp_sch_tfss=73,
  kmp_sch_mfsc=74,
  kmp_sch_fiss=75,
  kmp_sch_viss=76,
  kmp_sch_rnd=77,
  kmp_sch_fac2b=78, 
  //--------------LB4OMP_extensions----------------

  /* accessible only through KMP_SCHEDULE environment variable */
  kmp_sch_upper, /**< upper bound for unordered values */

  kmp_ord_lower = 64, /**< lower bound for ordered values, must be power of 2 */
  kmp_ord_static_chunked = 65,
  kmp_ord_static = 66, /**< ordered static unspecialized */
  kmp_ord_dynamic_chunked = 67,
  kmp_ord_guided_chunked = 68,
  kmp_ord_runtime = 69,
  kmp_ord_auto = 70, /**< ordered auto */
  kmp_ord_trapezoidal = 71,
  kmp_ord_upper, /**< upper bound for ordered values */

#if OMP_40_ENABLED
  /* Schedules for Distribute construct */
  kmp_distribute_static_chunked = 91, /**< distribute static chunked */
  kmp_distribute_static = 92, /**< distribute static unspecialized */
#endif

  /* For the "nomerge" versions, kmp_dispatch_next*() will always return a
     single iteration/chunk, even if the loop is serialized. For the schedule
     types listed above, the entire iteration vector is returned if the loop is
     serialized. This doesn't work for gcc/gcomp sections. */
  kmp_nm_lower = 160, /**< lower bound for nomerge values */

  kmp_nm_static_chunked =
      (kmp_sch_static_chunked - kmp_sch_lower + kmp_nm_lower),
  kmp_nm_static = 162, /**< static unspecialized */
  kmp_nm_dynamic_chunked = 163,
  kmp_nm_guided_chunked = 164, /**< guided unspecialized */
  kmp_nm_runtime = 165,
  kmp_nm_auto = 166, /**< auto */
  kmp_nm_trapezoidal = 167,

  /* accessible only through KMP_SCHEDULE environment variable */
  kmp_nm_static_greedy = 168,
  kmp_nm_static_balanced = 169,
  /* accessible only through KMP_SCHEDULE environment variable */
  kmp_nm_guided_iterative_chunked = 170,
  kmp_nm_guided_analytical_chunked = 171,
  kmp_nm_static_steal =
      172, /* accessible only through OMP_SCHEDULE environment variable */

  kmp_nm_ord_static_chunked = 193,
  kmp_nm_ord_static = 194, /**< ordered static unspecialized */
  kmp_nm_ord_dynamic_chunked = 195,
  kmp_nm_ord_guided_chunked = 196,
  kmp_nm_ord_runtime = 197,
  kmp_nm_ord_auto = 198, /**< auto */
  kmp_nm_ord_trapezoidal = 199,
  kmp_nm_upper, /**< upper bound for nomerge values */
```

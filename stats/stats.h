#ifndef YUV_BENCH_STATS_H
#define YUV_BENCH_STATS_H

#include <time.h>

typedef struct runStats runStats;
struct runStats {
    clock_t start;
    clock_t end;

    int i;

    double wasted;
    double mean;
    double min;
    double max;
    double sigma;
    double std_deviation;

    double* runs;
    int maxRuns;
};

void newRunStats(runStats *stats, int runs);

void clearRunStats(runStats *stats);

void startTime(runStats *stats);

void stopTime(runStats *stats);

#endif //YUV_BENCH_STATS_H

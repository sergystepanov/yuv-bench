#include <float.h>
#include <stdlib.h>
#include <math.h>
#include "stats.h"

void newRunStats(runStats *stats, int runs) {
    stats->wasted = 0;
    stats->mean = 0;
    stats->min = DBL_MAX;
    stats->max = 0;

    stats->sigma = 0;
    stats->std_deviation = 0;

    stats->i = 0;

    stats->maxRuns = runs;
    stats->runs = malloc(runs * sizeof(double));
}

void clearRunStats(runStats *stats) {
    free(stats->runs);
}

void calculate(runStats *stats) {
    stats->wasted = (double) (stats->end - stats->start) / CLOCKS_PER_SEC * 1000;
    int index = ++stats->i;
    stats->mean += (stats->wasted - stats->mean) / index;
    stats->runs[(index - 1) % stats->maxRuns] = stats->wasted;
    if (stats->wasted < stats->min) {
        stats->min = stats->wasted;
    }
    if (stats->wasted > stats->max) {
        stats->max = stats->wasted;
    }

    double sum = 0;
    for (int i = 0; i < stats->maxRuns; i++) {
        sum += pow((stats->runs[i] - stats->mean), 2);
    }
    stats->std_deviation = sqrt(sum / stats->maxRuns);
    stats->sigma = (/*min + max*/stats->mean);
}

void startTime(runStats *stats) {
    stats->start = clock();
}

void stopTime(runStats *stats) {
    stats->end = clock();
    calculate(stats);
}


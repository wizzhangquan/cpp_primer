#ifndef MUDUO_TEST_TIMESTAMP_H_
#define MUDUO_TEST_TIMESTAMP_H_
//google style : use fold path and filename
#include <string>
#include <stdint.h>

using std::string;

namespace muduo_test{

class Timestamp {
public:
    Timestamp()
        : microSecondsSinceEpoch_(0) { 
    }

    explicit Timestamp(int64_t microSecondsSinceEpoch)
        : microSecondsSinceEpoch_(microSecondsSinceEpoch) {
    }

    void swap(Timestamp &that) {
        std::swap(microSecondsSinceEpoch_, 
            that.microSecondsSinceEpoch_);
    }

    string toString();
    string toFormattedString(bool showMicroseconds = true);

    bool valid() const { return microSecondsSinceEpoch_ > 0; }

    int64_t microSecondsSinceEpoch() const { 
        return microSecondsSinceEpoch_;
    }
    time_t secondsSinceEpoch() const {
        return static_cast<time_t>(microSecondsSinceEpoch_
                     / kMicroSecondsPerSecond);
    }

    static Timestamp now();
    static Timestamp invalid() {
        return Timestamp();
    }

    static Timestamp fromUnixTime(time_t t, int microseconds = 0) {
        return Timestamp(static_cast<int64_t>(t) 
                     * kMicroSecondsPerSecond + microseconds);
    }

    static const int kMicroSecondsPerSecond = 1000 * 1000;

private:
    int64_t microSecondsSinceEpoch_;
};

inline bool operator==(const Timestamp &lhs, const Timestamp &rhs) {
    return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

inline bool operator<(const Timestamp &lhs, const Timestamp &rhs) {
    return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline double timeDifference(const Timestamp &high, const Timestamp &low) {
    int64_t diff = high.microSecondsSinceEpoch() -
                    low.microSecondsSinceEpoch();
    return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
}

inline Timestamp addTime(const Timestamp &timestamp, double seconds) {
    int64_t delta = static_cast<int64_t>(seconds 
            * Timestamp::kMicroSecondsPerSecond);
    return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
}

}

#endif

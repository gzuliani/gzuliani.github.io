#ifndef GUT_TAP_H
#define GUT_TAP_H

namespace gut {

class TapReport {
    std::ostream& os_;
    int testCount_;
    std::string testName_;
    std::vector<Notice> log_;
    bool quit_;
public:
    TapReport(std::ostream& os = std::cout) : os_(os) { }
    void onStart() {
        testCount_ = 0;
        quit_ = false;
    }
    void onEnd(int tests, int failedTests, int /*failures*/, double /*duration*/) {
        if (quit_)
            return;
        os_ << "1.." << tests << std::endl;
        if (tests > 0) {
            float okRatio = (tests - failedTests) * 100. / tests;
            os_
                << "# failed " << failedTests << "/" << tests << " test(s), "
                << std::fixed << std::setprecision(1)
                << okRatio << "% ok" << std::endl;
        }
    }
    void onStartTest(const std::string& name) {
        ++testCount_;
        testName_ = name;
    }
    void onEndTest(bool failed, double /*duration*/) {
        std::ostringstream oss;
        if (failed) {
            oss << "not ";
        }
        oss << "ok " << testCount_ << " - " << testName_;
        for (const auto& entry : log_) {
            oss << "\n# " << entry.toString();
        }
        os_ << oss.str() << std::endl;
        log_.clear();
    }
    void onFailure(const Notice& failure) {
        log_.push_back(failure);
    }
    void onEval(const Notice& expr) {
        log_.push_back(expr);
    }
    void onInfo(const Notice& info) {
        log_.push_back(info);
    }
    void onWarn(const Notice& warn) {
        log_.push_back(warn);
    }
    void onQuit(const std::string& reason) {
        quit_ = true;
        std::ostringstream oss;
        oss << "Bail out!";
        if (!reason.empty ())
            oss << " Reason: " << reason;
        os_ << oss.str() << std::endl;
    }
};

} // namespace gut

#define TODO(name_, desc_) \
    TEST(name_ " # todo " desc_)

#define SKIP(name_, reason_) \
    TEST(name_ " # skipped, reason: " reason_) { \
    } \
    void skip ## __LINE__()

#define BAIL_OUT(reason_) \
    do { \
        throw gut::AbortSuite(reason_); \
    } while (0)

#endif // GUT_TAP_H

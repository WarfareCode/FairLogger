/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// WARNING : pragma commands to hide boost warning
// TODO : remove these pragma commands when boost will fix this issue in future release

#include <Logger.h>

#include <iostream>
#include <vector>
#include <thread>

using namespace std;
using namespace fair;

namespace test
{

void printEverySeverity()
{
    static int i = 1;

    LOG(nolog) << "nolog message "   << i++;
    LOG(error) << "error message "   << i++;
    LOG(warn)  << "warning message " << i++;
    LOG(state) << "state message "   << i++;
    LOG(info)  << "info message "    << i++;
    LOG(debug) << "debug message "   << i++;
    LOG(debug1) << "debug1 message "   << i++;
    LOG(debug2) << "debug2 message "   << i++;
    LOG(debug3) << "debug3 message "   << i++;
    LOG(debug4) << "debug4 message "   << i++;
    LOG(trace) << "trace message "   << i++;
}

}

void printAllVerbositiesWithSeverity(Severity sev)
{
    Logger::SetConsoleSeverity(sev);

    cout << endl << "cout: >>> testing severity '" << Logger::SeverityName(sev) << "' with 'verylow' verbosity..." << endl;
    Logger::SetVerbosity(Verbosity::verylow);
    test::printEverySeverity();
    cout << endl << "cout: >>> testing severity '" << Logger::SeverityName(sev) << "' with 'low' verbosity..." << endl;
    Logger::SetVerbosity(Verbosity::low);
    test::printEverySeverity();
    cout << endl << "cout: >>> testing severity '" << Logger::SeverityName(sev) << "' with 'medium' verbosity..." << endl;
    Logger::SetVerbosity(Verbosity::medium);
    test::printEverySeverity();
    cout << endl << "cout: >>> testing severity '" << Logger::SeverityName(sev) << "' with 'high' verbosity..." << endl;
    Logger::SetVerbosity(Verbosity::high);
    test::printEverySeverity();
    cout << endl << "cout: >>> testing severity '" << Logger::SeverityName(sev) << "' with 'veryhigh' verbosity..." << endl;
    Logger::SetVerbosity(Verbosity::veryhigh);
    test::printEverySeverity();
    cout << endl << "cout: >>> testing severity '" << Logger::SeverityName(sev) << "' with 'user1' verbosity..." << endl;
    Logger::SetVerbosity(Verbosity::user1);
    test::printEverySeverity();
    cout << endl << "cout: >>> testing severity '" << Logger::SeverityName(sev) << "' with 'user2' verbosity..." << endl;
    Logger::SetVerbosity(Verbosity::user2);
    test::printEverySeverity();
    cout << endl << "cout: >>> testing severity '" << Logger::SeverityName(sev) << "' with 'user3' verbosity..." << endl;
    Logger::SetVerbosity(Verbosity::user3);
    test::printEverySeverity();
    cout << endl << "cout: >>> testing severity '" << Logger::SeverityName(sev) << "' with 'user4' verbosity..." << endl;
    Logger::SetVerbosity(Verbosity::user4);
    test::printEverySeverity();
}

void silentlyPrintAllVerbositiesWithSeverity(Severity sev)
{
    Logger::SetConsoleSeverity(sev);

    Logger::SetVerbosity(Verbosity::verylow);
    test::printEverySeverity();
    Logger::SetVerbosity(Verbosity::low);
    test::printEverySeverity();
    Logger::SetVerbosity(Verbosity::medium);
    test::printEverySeverity();
    Logger::SetVerbosity(Verbosity::high);
    test::printEverySeverity();
    Logger::SetVerbosity(Verbosity::veryhigh);
    test::printEverySeverity();
    Logger::SetVerbosity(Verbosity::user1);
    test::printEverySeverity();
    Logger::SetVerbosity(Verbosity::user2);
    test::printEverySeverity();
    Logger::SetVerbosity(Verbosity::user3);
    test::printEverySeverity();
    Logger::SetVerbosity(Verbosity::user4);
    test::printEverySeverity();
}

int main()
{
    Logger::SetConsoleColor(true);

    auto spec = VerbositySpec::Make(VerbositySpec::Info::file_line_function,
                                    VerbositySpec::Info::process_name,VerbositySpec::Info::process_name);
    cout << "Defining custom verbosity \"user2\"" << endl;
    Logger::DefineVerbosity(Verbosity::user2, spec);

    cout << "cout: testing severities..." << endl;

    printAllVerbositiesWithSeverity(Severity::trace);
    printAllVerbositiesWithSeverity(Severity::debug4);
    printAllVerbositiesWithSeverity(Severity::debug3);
    printAllVerbositiesWithSeverity(Severity::debug2);
    printAllVerbositiesWithSeverity(Severity::debug1);
    printAllVerbositiesWithSeverity(Severity::debug);
    printAllVerbositiesWithSeverity(Severity::info);
    printAllVerbositiesWithSeverity(Severity::state);
    printAllVerbositiesWithSeverity(Severity::warn);
    printAllVerbositiesWithSeverity(Severity::error);
    printAllVerbositiesWithSeverity(Severity::nolog);

    cout << endl;
    cout << "cout: resetting severity to 'info' and verbosity to 'medium'" << endl;
    Logger::SetConsoleSeverity(Severity::info);
    Logger::SetVerbosity(Verbosity::medium);

    cout << "cout: is logging trace: " << fair::Logger::Logging(Severity::trace) << endl;
    cout << "cout: is logging debug4: " << fair::Logger::Logging(Severity::debug) << endl;
    cout << "cout: is logging debug3: " << fair::Logger::Logging(Severity::debug) << endl;
    cout << "cout: is logging debug2: " << fair::Logger::Logging(Severity::debug) << endl;
    cout << "cout: is logging debug1: " << fair::Logger::Logging(Severity::debug) << endl;
    cout << "cout: is logging debug: " << fair::Logger::Logging(Severity::debug) << endl;
    cout << "cout: is logging info: " << fair::Logger::Logging(Severity::info) << endl;
    cout << "cout: is logging state: " << fair::Logger::Logging(Severity::state) << endl;
    cout << "cout: is logging warn: " << fair::Logger::Logging(Severity::warn) << endl;
    cout << "cout: is logging error: " << fair::Logger::Logging(Severity::error) << endl;
    cout << "cout: is logging fatal: " << fair::Logger::Logging(Severity::fatal) << endl;
    cout << "cout: is logging nolog: " << fair::Logger::Logging(Severity::nolog) << endl;

    for (int i = 0; i < 1000000; ++i)
    {
        silentlyPrintAllVerbositiesWithSeverity(Severity::nolog);
    }
    cout << endl;
    cout << "cout: resetting severity to 'trace' and verbosity to 'veryhigh'" << endl;
    Logger::SetConsoleSeverity(Severity::trace);
    Logger::SetVerbosity(Verbosity::veryhigh);

    cout << endl;
    cout << "cout: testing conditional logging..." << endl;
    int x = 0;
    LOG(info) << "x = " << x << " (initial)";
    LOG_IF(info, (x == 0)) << "incrementing x to " << ++x;
    LOG(info) << "x = " << x << " (after increment)";
    LOG_IF(info, (x == 0)) << "this should not be printed and x not incremented: " << ++x;
    LOG(info) << "x = " << x << " (after conditional increment)";

    cout << endl;
    cout << "cout: resetting severity to 'nolog'" << endl;
    Logger::SetConsoleSeverity(Severity::nolog);

    cout << "cout: ----------------------------" << endl;
    cout << "cout: open log file with severity 'error'" << endl;
    Logger::InitFileSink(Severity::error, "test_log", true);
    test::printEverySeverity();
    cout << "cout: closing log file" << endl;
    Logger::RemoveFileSink();


    cout << "cout: resetting severity to 'nolog'" << endl;
    Logger::SetConsoleSeverity(Severity::nolog);
    cout << "cout: ----------------------------" << endl;
    cout << "cout: adding custom sink with error severity" << endl << endl;

    Logger::AddCustomSink("CustomSink", "error", [](const string& content, const LogMetaData& metadata)
    {
        cout << "CustomSink: content: " << content << endl;

        cout << "CustomSink: available metadata: " << endl;
        cout << "CustomSink: \tstd::time_t timestamp: " << metadata.timestamp << endl;
        cout << "CustomSink: \tstd::chrono::microseconds us: " << metadata.us.count() << endl;
        cout << "CustomSink: \tstd::string process_name: " << metadata.process_name << endl;
        cout << "CustomSink: \tstd::string file: " << metadata.file << endl;
        cout << "CustomSink: \tstd::string line: " << metadata.line << endl;
        cout << "CustomSink: \tstd::string func: " << metadata.func << endl;
        cout << "CustomSink: \tstd::string severity_name: " << metadata.severity_name << endl;
        cout << "CustomSink: \tfair::Severity severity: " << static_cast<int>(metadata.severity) << endl;
    });

    test::printEverySeverity();

    cout << endl << "cout: removing custom sink with info severity" << endl;

    Logger::AddCustomSink("CustomSink", Severity::error, [](const string& content, const LogMetaData& metadata){});
    Logger::RemoveCustomSink("CustomSink");
    Logger::RemoveCustomSink("bla");

    return 0;
}

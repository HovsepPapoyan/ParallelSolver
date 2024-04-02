/**
 * @file SolverUnitTests.cpp
 *
 * @brief SolverUnitTests test class for providing test methods for Solver project.
 *
 * @author Hovsep Papoyan
 * Contact: papoyanhovsep93@gmail.com
 * @Date 2024-03-28
 *
 */

#include "CppUnitTest.h"
#include "../Solver/InputValidator.h"
#include "../Solver/Solver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SolverUnitTests
{
	TEST_CLASS(SolverUnitTests)
	{
	public:
		TEST_METHOD(InputValidatorTests)
		{
			std::optional<std::vector<int>> res1{ std::nullopt };

			// Testing of argc (negative).
			const char* const argv1[]{ "ProgramName" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv1) / sizeof(argv1[0]), argv1), L"InputValidatorTest1");

			const char* const argv2[]{ "ProgramName", "1" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv2) / sizeof(argv2[0]), argv2), L"InputValidatorTest2");

			const char* const argv3[]{ "ProgramName", "1", "2" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv3) / sizeof(argv3[0]), argv3), L"InputValidatorTest3");

			const char* const argv4[]{ "ProgramName", "1", "2", "3", "4" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv4) / sizeof(argv4[0]), argv4), L"InputValidatorTest4");

			// Testing of argv (negative).
			const char* const argv5[]{ "ProgramName", "1", "2", "3.4"};
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv5) / sizeof(argv5[0]), argv5), L"InputValidatorTest5");

			const char* const argv6[]{ "ProgramName", "1", "2", "." };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv6) / sizeof(argv6[0]), argv6), L"InputValidatorTest6");

			const char* const argv7[]{ "ProgramName", "-1", "0", "1-" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv7) / sizeof(argv7[0]), argv7), L"InputValidatorTest7");

			const char* const argv8[]{ "ProgramName", "1", "2", "-0" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv8) / sizeof(argv8[0]), argv8), L"InputValidatorTest8");

			const char* const argv9[]{ "ProgramName", "1", "2", "000" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv9) / sizeof(argv9[0]), argv9), L"InputValidatorTest9");

			const char* const argv10[]{ "ProgramName", "+5", "-6", "-7" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv10) / sizeof(argv10[0]), argv10), L"InputValidatorTest10");

			const char* const argv11[]{ "ProgramName", "1", "2", "a" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv11) / sizeof(argv11[0]), argv11), L"InputValidatorTest11");

			const char* const argv12[]{ "ProgramName", "1", "2", "aaaaa" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv12) / sizeof(argv12[0]), argv12), L"InputValidatorTest12");

			const char* const argv13[]{ "ProgramName", "1", "2", "0x01" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv13) / sizeof(argv13[0]), argv13), L"InputValidatorTest13");

			const char* const argv14[]{ "ProgramName", "1", "2", "0234" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv14) / sizeof(argv14[0]), argv14), L"InputValidatorTest14");

			const char* const argv15[]{ "ProgramName", "1a", "2", "3" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv15) / sizeof(argv15[0]), argv15), L"InputValidatorTest15");

			const char* const argv16[]{ "ProgramName", "77777777777777", "1", "2" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv16) / sizeof(argv16[0]), argv16), L"InputValidatorTest16");

			// Testing of argc and argv (positive)
			res1 = { 1,2,3 };
			const char* const argv17[]{ "ProgramName", "1", "2", "3" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv17) / sizeof(argv17[0]), argv17), L"InputValidatorTest17");
			
			res1 = { 1,2,3,4,5,6 };
			const char* const argv18[]{ "ProgramName", "1", "2", "3", "4", "5", "6" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv18) / sizeof(argv18[0]), argv18), L"InputValidatorTest18");

			res1 = { 1,2,0 };
			const char* const argv19[]{ "ProgramName", "1", "2", "0" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv19) / sizeof(argv19[0]), argv19), L"InputValidatorTest19");

			res1 = { 1,0,2 };
			const char* const argv20[]{ "ProgramName", "1", "0", "2" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv20) / sizeof(argv20[0]), argv20), L"InputValidatorTest20");

			res1 = { 1,0,0 };
			const char* const argv21[]{ "ProgramName", "1", "0", "0" };
			Assert::IsTrue(res1 == InputValidator::getValidatedInput(sizeof(argv21) / sizeof(argv21[0]), argv21), L"InputValidatorTest21");
		}
		TEST_METHOD(SolverLinearTests)
		{
			using namespace slv;

			Solver::Result res1 = -1.0;
			Solver::Result res2 = Solver::solve(0.0, 1.0, 1.0);
			Assert::IsTrue(std::holds_alternative<Solver::LinearResult>(res2) &&
			    (std::get<Solver::LinearResult>(res1) == std::get<Solver::LinearResult>(res2)), L"SolverLinearTest1");

			res1 = 1.0;
			res2 = Solver::solve(0.0, -1.0, 1.0);
			Assert::IsTrue(std::holds_alternative<Solver::LinearResult>(res2) &&
			    (std::get<Solver::LinearResult>(res1) == std::get<Solver::LinearResult>(res2)), L"SolverLinearTest2");

			res1 = -1.0;
			res2 = Solver::solve(0.0, -1.0, -1.0);
			Assert::IsTrue(std::holds_alternative<Solver::LinearResult>(res2) &&
				(std::get<Solver::LinearResult>(res1) == std::get<Solver::LinearResult>(res2)), L"SolverLinearTest3");

			res1 = 1.0;
			res2 = Solver::solve(0.0, 1.0, -1.0);
			Assert::IsTrue(std::holds_alternative<Solver::LinearResult>(res2) &&
				(std::get<Solver::LinearResult>(res1) == std::get<Solver::LinearResult>(res2)), L"SolverLinearTest4");

			res1 = std::nullopt;
			res2 = Solver::solve(0.0, 0.0, 1.0);
			Assert::IsTrue(std::holds_alternative<Solver::LinearResult>(res2) &&
				(std::get<Solver::LinearResult>(res1) == std::get<Solver::LinearResult>(res2)), L"SolverLinearTest5");

			res1 = std::nullopt;
			res2 = Solver::solve(0.0, 0.0, 0.0);
			Assert::IsTrue(std::holds_alternative<Solver::LinearResult>(res2) &&
				(std::get<Solver::LinearResult>(res1) == std::get<Solver::LinearResult>(res2)), L"SolverLinearTest6");
		}
		TEST_METHOD(SolverQuadraticTests)
		{
			using namespace slv;

			// Dicriminant == 0
			Solver::Result res1 = Solver::QuadraticResult{ std::make_pair(-1.0, -1.0), 0.0, -1.0 };
			Solver::Result res2 = Solver::solve(1.0, 2.0, 1.0);
			Assert::IsTrue(std::holds_alternative<Solver::QuadraticResult>(res2));
			const auto& refRes1 = std::get<Solver::QuadraticResult>(res1);
			const auto& refRes2 = std::get<Solver::QuadraticResult>(res2);
			Assert::IsTrue(refRes1.m_roots == refRes2.m_roots &&
				refRes1.m_extremum == refRes2.m_extremum &&
				refRes1.m_criticalPoint == refRes2.m_criticalPoint, L"SolverQuadraticTest1");

			// Dicriminant < 0
			res1 = Solver::QuadraticResult{ std::nullopt, 9.75, -0.5 };
			res2 = Solver::solve(1.0, 1.0, 10.0);
			Assert::IsTrue(std::holds_alternative<Solver::QuadraticResult>(res2));
			Assert::IsTrue(refRes1.m_roots == refRes2.m_roots &&
				refRes1.m_extremum == refRes2.m_extremum &&
				refRes1.m_criticalPoint == refRes2.m_criticalPoint, L"SolverQuadraticTest2");

			// Dicriminant > 0
			res1 = Solver::QuadraticResult{ std::make_pair(-6.0, -1.0), -6.25, -3.5 };
			res2 = Solver::solve(1.0, 7.0, 6.0);
			Assert::IsTrue(std::holds_alternative<Solver::QuadraticResult>(res2));
			Assert::IsTrue(refRes1.m_roots == refRes2.m_roots &&
				refRes1.m_extremum == refRes2.m_extremum &&
				refRes1.m_criticalPoint == refRes2.m_criticalPoint, L"SolverQuadraticTest3");
		}
	};
}

// Copyright(C) 2015 kittikun
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sub-license, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// This work is compatible with the Dominion Rules role-playing system.To learn more about
// Dominion Rules, visit the Dominion Rules web site at <http://www.dominionrules.org>

#include <gtest/gtest.h>

#include <memory>

#include <generated/style_generated.h>
#include <generated/style_array_generated.h>

#include <dominion/api.h>
#include <dominion/core/database.h>
#include <dominion/character/style.h>
#include <dominion/character/skill_template.h>

namespace DominionTest
{
	class DatabaseTest : public testing::Test
	{
	public:
		DatabaseTest()
			: api_(new Dominion::Api())
		{
		}

	protected:
		void SetUp() override
		{
			api_->InitializeFromMemory();
			database_ = api_->GetDatabase();
		}

	public:
		std::unique_ptr<Dominion::Api> api_;
		std::shared_ptr<Dominion::DataBase> database_;
	};

	TEST_F(DatabaseTest, GetVersion)
	{
		auto version = database_->GetVersion();

		EXPECT_GE(version, static_cast<uint32_t>(1));
	}

	TEST_F(DatabaseTest, GetSkillTemplates)
	{
		auto templates = database_->GetSkillTemplates();

		EXPECT_GT(templates.size(), static_cast<uint32_t>(0));

		for (auto skt : templates) {
			EXPECT_GT(skt->name().size(), static_cast<uint32_t>(0));
			EXPECT_NO_THROW(skt->type());
		}
	}

	TEST_F(DatabaseTest, GetStyles)
	{
		auto styles = database_->GetStyles();

		EXPECT_GT(styles.size(), static_cast<uint32_t>(0));

		bool hasPriest = false;
		bool hasWitch = false;

		for (auto style : styles) {
			EXPECT_GT(style->name().size(), static_cast<uint32_t>(0));

			hasPriest |= style->isPriest();
			hasWitch |= style->isWitch();
		}

		EXPECT_TRUE(hasPriest);
		EXPECT_TRUE(hasWitch);
	}

	TEST_F(DatabaseTest, GetStylesSerializiation)
	{
		std::string buffer;
		auto styles = database_->SerializeStyles(buffer);
		flatbuffers::Verifier verifier(styles.get(), buffer.size());

		EXPECT_TRUE(Dominion::VerifyFBStyleArrayBuffer(verifier));
	}
} // namespace DominionTest
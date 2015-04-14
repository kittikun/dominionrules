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

#include <dominion/capi/capi.h>
#include <dominion/capi/cdice.h>
#include <dominion/capi/cDatabase.h>

#include <generated/style_generated.h>
#include <generated/style_array_generated.h>

namespace DominionTest
{
	class CApiTest : public testing::Test
	{
	public:
		CApiTest()
		{
			InitializeFromMemory();
		}
	};

	TEST_F(CApiTest, Dice)
	{
		auto handle = CreateDice();

		EXPECT_GT(handle, 0);

		auto rnd = Roll(handle);

		EXPECT_TRUE((rnd > 0) && (rnd <= 12));

		EXPECT_NO_THROW(DestroyDice(handle));
	}

	TEST_F(CApiTest, Styles)
	{
		auto handle = SerializeStyles();
		auto size = GetBufferSize(handle);
		EXPECT_GT(size, 0);

		std::string buffer(size, 'e');

		auto getRes = GetBuffer(handle, &buffer[0]);

		EXPECT_TRUE(getRes);

		flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t *>(buffer.c_str()), size);
		EXPECT_TRUE(FBDominion::VerifyStyleArrayBuffer(verifier));

		EXPECT_NO_THROW(ReleaseBuffer(handle));
	}

	TEST_F(CApiTest, Perks)
	{
		auto handle = SerializePerks();
		auto size = GetBufferSize(handle);
		EXPECT_GT(size, 0);

		std::string buffer(size, 'e');

		auto getRes = GetBuffer(handle, &buffer[0]);

		EXPECT_TRUE(getRes);

		flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t *>(buffer.c_str()), size);
		EXPECT_TRUE(FBDominion::VerifyStyleArrayBuffer(verifier));

		EXPECT_NO_THROW(ReleaseBuffer(handle));
	}
} // namespace DominionTest
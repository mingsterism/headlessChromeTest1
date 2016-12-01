// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/json/json_reader.h"
#include "base/json/json_string_value_serializer.h"
#include "headless/public/devtools/domains/accessibility.h"
#include "headless/public/devtools/domains/dom.h"
#include "headless/public/devtools/domains/memory.h"
#include "headless/public/devtools/domains/page.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace headless {

TEST(TypesTest, IntegerProperty) {
  std::unique_ptr<page::NavigateToHistoryEntryParams> object(
      page::NavigateToHistoryEntryParams::Builder().SetEntryId(123).Build());
  EXPECT_TRUE(object);
  EXPECT_EQ(123, object->GetEntryId());

  std::unique_ptr<page::NavigateToHistoryEntryParams> clone(object->Clone());
  EXPECT_TRUE(clone);
  EXPECT_EQ(123, clone->GetEntryId());
}

TEST(TypesTest, IntegerPropertyParseError) {
  const char* json = "{\"entryId\": \"foo\"}";
  std::unique_ptr<base::Value> object = base::JSONReader::Read(json);
  EXPECT_TRUE(object);

#if DCHECK_IS_ON()
  ErrorReporter errors;
  EXPECT_FALSE(page::NavigateToHistoryEntryParams::Parse(*object, &errors));
  EXPECT_TRUE(errors.HasErrors());
#endif  // DCHECK_IS_ON()
}

TEST(TypesTest, BooleanProperty) {
  std::unique_ptr<memory::SetPressureNotificationsSuppressedParams> object(
      memory::SetPressureNotificationsSuppressedParams::Builder()
          .SetSuppressed(true)
          .Build());
  EXPECT_TRUE(object);
  EXPECT_TRUE(object->GetSuppressed());

  std::unique_ptr<memory::SetPressureNotificationsSuppressedParams> clone(
      object->Clone());
  EXPECT_TRUE(clone);
  EXPECT_TRUE(clone->GetSuppressed());
}

TEST(TypesTest, BooleanPropertyParseError) {
  const char* json = "{\"suppressed\": \"foo\"}";
  std::unique_ptr<base::Value> object = base::JSONReader::Read(json);
  EXPECT_TRUE(object);

#if DCHECK_IS_ON()
  ErrorReporter errors;
  EXPECT_FALSE(memory::SetPressureNotificationsSuppressedParams::Parse(
      *object, &errors));
  EXPECT_TRUE(errors.HasErrors());
#endif  // DCHECK_IS_ON()
}

TEST(TypesTest, DoubleProperty) {
  std::unique_ptr<page::SetGeolocationOverrideParams> object(
      page::SetGeolocationOverrideParams::Builder().SetLatitude(3.14).Build());
  EXPECT_TRUE(object);
  EXPECT_EQ(3.14, object->GetLatitude());

  std::unique_ptr<page::SetGeolocationOverrideParams> clone(object->Clone());
  EXPECT_TRUE(clone);
  EXPECT_EQ(3.14, clone->GetLatitude());
}

TEST(TypesTest, DoublePropertyParseError) {
  const char* json = "{\"latitude\": \"foo\"}";
  std::unique_ptr<base::Value> object = base::JSONReader::Read(json);
  EXPECT_TRUE(object);

#if DCHECK_IS_ON()
  ErrorReporter errors;
  EXPECT_FALSE(page::SetGeolocationOverrideParams::Parse(*object, &errors));
  EXPECT_TRUE(errors.HasErrors());
#endif  // DCHECK_IS_ON()
}

TEST(TypesTest, StringProperty) {
  std::unique_ptr<page::NavigateParams> object(
      page::NavigateParams::Builder().SetUrl("url").Build());
  EXPECT_TRUE(object);
  EXPECT_EQ("url", object->GetUrl());

  std::unique_ptr<page::NavigateParams> clone(object->Clone());
  EXPECT_TRUE(clone);
  EXPECT_EQ("url", clone->GetUrl());
}

TEST(TypesTest, StringPropertyParseError) {
  const char* json = "{\"url\": false}";
  std::unique_ptr<base::Value> object = base::JSONReader::Read(json);
  EXPECT_TRUE(object);

#if DCHECK_IS_ON()
  ErrorReporter errors;
  EXPECT_FALSE(page::NavigateParams::Parse(*object, &errors));
  EXPECT_TRUE(errors.HasErrors());
#endif  // DCHECK_IS_ON()
}

TEST(TypesTest, EnumProperty) {
  std::unique_ptr<runtime::RemoteObject> object(
      runtime::RemoteObject::Builder()
          .SetType(runtime::RemoteObjectType::UNDEFINED)
          .Build());
  EXPECT_TRUE(object);
  EXPECT_EQ(runtime::RemoteObjectType::UNDEFINED, object->GetType());

  std::unique_ptr<runtime::RemoteObject> clone(object->Clone());
  EXPECT_TRUE(clone);
  EXPECT_EQ(runtime::RemoteObjectType::UNDEFINED, clone->GetType());
}

TEST(TypesTest, EnumPropertyParseError) {
  const char* json = "{\"type\": false}";
  std::unique_ptr<base::Value> object = base::JSONReader::Read(json);
  EXPECT_TRUE(object);

#if DCHECK_IS_ON()
  ErrorReporter errors;
  EXPECT_FALSE(runtime::RemoteObject::Parse(*object, &errors));
  EXPECT_TRUE(errors.HasErrors());
#endif  // DCHECK_IS_ON()
}

TEST(TypesTest, ArrayProperty) {
  std::vector<int> values;
  values.push_back(1);
  values.push_back(2);
  values.push_back(3);

  std::unique_ptr<dom::QuerySelectorAllResult> object(
      dom::QuerySelectorAllResult::Builder().SetNodeIds(values).Build());
  EXPECT_TRUE(object);
  EXPECT_EQ(3u, object->GetNodeIds()->size());
  EXPECT_EQ(1, object->GetNodeIds()->at(0));
  EXPECT_EQ(2, object->GetNodeIds()->at(1));
  EXPECT_EQ(3, object->GetNodeIds()->at(2));

  std::unique_ptr<dom::QuerySelectorAllResult> clone(object->Clone());
  EXPECT_TRUE(clone);
  EXPECT_EQ(3u, clone->GetNodeIds()->size());
  EXPECT_EQ(1, clone->GetNodeIds()->at(0));
  EXPECT_EQ(2, clone->GetNodeIds()->at(1));
  EXPECT_EQ(3, clone->GetNodeIds()->at(2));
}

TEST(TypesTest, ArrayPropertyParseError) {
  const char* json = "{\"nodeIds\": true}";
  std::unique_ptr<base::Value> object = base::JSONReader::Read(json);
  EXPECT_TRUE(object);

#if DCHECK_IS_ON()
  ErrorReporter errors;
  EXPECT_FALSE(dom::QuerySelectorAllResult::Parse(*object, &errors));
  EXPECT_TRUE(errors.HasErrors());
#endif  // DCHECK_IS_ON()
}

TEST(TypesTest, ObjectProperty) {
  std::unique_ptr<runtime::RemoteObject> subobject(
      runtime::RemoteObject::Builder()
          .SetType(runtime::RemoteObjectType::SYMBOL)
          .Build());
  std::unique_ptr<runtime::EvaluateResult> object(
      runtime::EvaluateResult::Builder()
          .SetResult(std::move(subobject))
          .Build());
  EXPECT_TRUE(object);
  EXPECT_EQ(runtime::RemoteObjectType::SYMBOL, object->GetResult()->GetType());

  std::unique_ptr<runtime::EvaluateResult> clone(object->Clone());
  EXPECT_TRUE(clone);
  EXPECT_EQ(runtime::RemoteObjectType::SYMBOL, clone->GetResult()->GetType());
}

TEST(TypesTest, ObjectPropertyParseError) {
  const char* json = "{\"result\": 42}";
  std::unique_ptr<base::Value> object = base::JSONReader::Read(json);
  EXPECT_TRUE(object);

#if DCHECK_IS_ON()
  ErrorReporter errors;
  EXPECT_FALSE(runtime::EvaluateResult::Parse(*object, &errors));
  EXPECT_TRUE(errors.HasErrors());
#endif  // DCHECK_IS_ON()
}

TEST(TypesTest, AnyProperty) {
  std::unique_ptr<base::Value> value(new base::FundamentalValue(123));
  std::unique_ptr<accessibility::AXValue> object(
      accessibility::AXValue::Builder()
          .SetType(accessibility::AXValueType::INTEGER)
          .SetValue(std::move(value))
          .Build());
  EXPECT_TRUE(object);
  EXPECT_EQ(base::Value::TYPE_INTEGER, object->GetValue()->GetType());

  std::unique_ptr<accessibility::AXValue> clone(object->Clone());
  EXPECT_TRUE(clone);
  EXPECT_EQ(base::Value::TYPE_INTEGER, clone->GetValue()->GetType());

  int clone_value;
  EXPECT_TRUE(clone->GetValue()->GetAsInteger(&clone_value));
  EXPECT_EQ(123, clone_value);
}

TEST(TypesTest, ComplexObjectClone) {
  std::vector<std::unique_ptr<dom::Node>> child_nodes;
  child_nodes.emplace_back(dom::Node::Builder()
                               .SetNodeId(1)
                               .SetBackendNodeId(2)
                               .SetNodeType(3)
                               .SetNodeName("-blink-blink")
                               .SetLocalName("-blink-blink")
                               .SetNodeValue("-blink-blink")
                               .Build());
  std::unique_ptr<dom::SetChildNodesParams> params =
      dom::SetChildNodesParams::Builder()
          .SetParentId(123)
          .SetNodes(std::move(child_nodes))
          .Build();
  std::unique_ptr<dom::SetChildNodesParams> clone = params->Clone();
  ASSERT_NE(nullptr, clone);

  std::string orig;
  JSONStringValueSerializer(&orig).Serialize(*params->Serialize());
  std::string clone_value;
  JSONStringValueSerializer(&clone_value).Serialize(*clone->Serialize());
  EXPECT_EQ(orig, clone_value);
}

}  // namespace headless

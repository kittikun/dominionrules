// automatically generated, do not modify

namespace Dominion
{

using FlatBuffers;

public class FBStyleArray : Table {
  public static FBStyleArray GetRootAsFBStyleArray(ByteBuffer _bb) { return GetRootAsFBStyleArray(_bb, new FBStyleArray()); }
  public static FBStyleArray GetRootAsFBStyleArray(ByteBuffer _bb, FBStyleArray obj) { return (obj.__init(_bb.GetInt(_bb.position()) + _bb.position(), _bb)); }
  public FBStyleArray __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public FBStyle Values(int j) { return Values(new FBStyle(), j); }
  public FBStyle Values(FBStyle obj, int j) { int o = __offset(4); return o != 0 ? obj.__init(__indirect(__vector(o) + j * 4), bb) : null; }
  public int ValuesLength() { int o = __offset(4); return o != 0 ? __vector_len(o) : 0; }

  public static int CreateFBStyleArray(FlatBufferBuilder builder,
      int values = 0) {
    builder.StartObject(1);
    FBStyleArray.AddValues(builder, values);
    return FBStyleArray.EndFBStyleArray(builder);
  }

  public static void StartFBStyleArray(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddValues(FlatBufferBuilder builder, int valuesOffset) { builder.AddOffset(0, valuesOffset, 0); }
  public static int CreateValuesVector(FlatBufferBuilder builder, int[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i]); return builder.EndVector(); }
  public static void StartValuesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static int EndFBStyleArray(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return o;
  }
  public static void FinishFBStyleArrayBuffer(FlatBufferBuilder builder, int offset) { builder.Finish(offset); }
};


}

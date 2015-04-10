// automatically generated, do not modify

namespace Dominion
{

using FlatBuffers;

public class FBStyle : Table {
  public static FBStyle GetRootAsFBStyle(ByteBuffer _bb) { return GetRootAsFBStyle(_bb, new FBStyle()); }
  public static FBStyle GetRootAsFBStyle(ByteBuffer _bb, FBStyle obj) { return (obj.__init(_bb.GetInt(_bb.position()) + _bb.position(), _bb)); }
  public FBStyle __init(int _i, ByteBuffer _bb) { bb_pos = _i; bb = _bb; return this; }

  public uint Id() { int o = __offset(4); return o != 0 ? bb.GetUint(o + bb_pos) : (uint)0; }
  public string Name() { int o = __offset(6); return o != 0 ? __string(o + bb_pos) : null; }
  public bool IsBeast() { int o = __offset(8); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; }
  public bool IsPriest() { int o = __offset(10); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; }
  public bool IsWitch() { int o = __offset(12); return o != 0 ? 0!=bb.Get(o + bb_pos) : (bool)false; }

  public static int CreateFBStyle(FlatBufferBuilder builder,
      uint id = 0,
      int name = 0,
      bool isBeast = false,
      bool isPriest = false,
      bool isWitch = false) {
    builder.StartObject(5);
    FBStyle.AddName(builder, name);
    FBStyle.AddId(builder, id);
    FBStyle.AddIsWitch(builder, isWitch);
    FBStyle.AddIsPriest(builder, isPriest);
    FBStyle.AddIsBeast(builder, isBeast);
    return FBStyle.EndFBStyle(builder);
  }

  public static void StartFBStyle(FlatBufferBuilder builder) { builder.StartObject(5); }
  public static void AddId(FlatBufferBuilder builder, uint id) { builder.AddUint(0, id, 0); }
  public static void AddName(FlatBufferBuilder builder, int nameOffset) { builder.AddOffset(1, nameOffset, 0); }
  public static void AddIsBeast(FlatBufferBuilder builder, bool isBeast) { builder.AddBool(2, isBeast, false); }
  public static void AddIsPriest(FlatBufferBuilder builder, bool isPriest) { builder.AddBool(3, isPriest, false); }
  public static void AddIsWitch(FlatBufferBuilder builder, bool isWitch) { builder.AddBool(4, isWitch, false); }
  public static int EndFBStyle(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    builder.Required(o, 6);  // name
    return o;
  }
  public static void FinishFBStyleBuffer(FlatBufferBuilder builder, int offset) { builder.Finish(offset); }
};


}

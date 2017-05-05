// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: paxos.proto

#ifndef PROTOBUF_paxos_2eproto__INCLUDED
#define PROTOBUF_paxos_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace libpaxos {
class BeginRound;
class BeginRoundDefaultTypeInternal;
extern BeginRoundDefaultTypeInternal _BeginRound_default_instance_;
class LastVote;
class LastVoteDefaultTypeInternal;
extern LastVoteDefaultTypeInternal _LastVote_default_instance_;
class NextRound;
class NextRoundDefaultTypeInternal;
extern NextRoundDefaultTypeInternal _NextRound_default_instance_;
class Voted;
class VotedDefaultTypeInternal;
extern VotedDefaultTypeInternal _Voted_default_instance_;
}  // namespace libpaxos

namespace libpaxos {

namespace protobuf_paxos_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_paxos_2eproto

// ===================================================================

class NextRound : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:libpaxos.NextRound) */ {
 public:
  NextRound();
  virtual ~NextRound();

  NextRound(const NextRound& from);

  inline NextRound& operator=(const NextRound& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const NextRound& default_instance();

  static inline const NextRound* internal_default_instance() {
    return reinterpret_cast<const NextRound*>(
               &_NextRound_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(NextRound* other);

  // implements Message ----------------------------------------------

  inline NextRound* New() const PROTOBUF_FINAL { return New(NULL); }

  NextRound* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const NextRound& from);
  void MergeFrom(const NextRound& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(NextRound* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // uint64 roundNumber = 1;
  void clear_roundnumber();
  static const int kRoundNumberFieldNumber = 1;
  ::google::protobuf::uint64 roundnumber() const;
  void set_roundnumber(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:libpaxos.NextRound)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint64 roundnumber_;
  mutable int _cached_size_;
  friend struct protobuf_paxos_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class LastVote : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:libpaxos.LastVote) */ {
 public:
  LastVote();
  virtual ~LastVote();

  LastVote(const LastVote& from);

  inline LastVote& operator=(const LastVote& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const LastVote& default_instance();

  static inline const LastVote* internal_default_instance() {
    return reinterpret_cast<const LastVote*>(
               &_LastVote_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(LastVote* other);

  // implements Message ----------------------------------------------

  inline LastVote* New() const PROTOBUF_FINAL { return New(NULL); }

  LastVote* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const LastVote& from);
  void MergeFrom(const LastVote& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(LastVote* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // uint64 roundNumber = 1;
  void clear_roundnumber();
  static const int kRoundNumberFieldNumber = 1;
  ::google::protobuf::uint64 roundnumber() const;
  void set_roundnumber(::google::protobuf::uint64 value);

  // uint64 lastRound = 2;
  void clear_lastround();
  static const int kLastRoundFieldNumber = 2;
  ::google::protobuf::uint64 lastround() const;
  void set_lastround(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:libpaxos.LastVote)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint64 roundnumber_;
  ::google::protobuf::uint64 lastround_;
  mutable int _cached_size_;
  friend struct protobuf_paxos_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class BeginRound : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:libpaxos.BeginRound) */ {
 public:
  BeginRound();
  virtual ~BeginRound();

  BeginRound(const BeginRound& from);

  inline BeginRound& operator=(const BeginRound& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const BeginRound& default_instance();

  static inline const BeginRound* internal_default_instance() {
    return reinterpret_cast<const BeginRound*>(
               &_BeginRound_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void Swap(BeginRound* other);

  // implements Message ----------------------------------------------

  inline BeginRound* New() const PROTOBUF_FINAL { return New(NULL); }

  BeginRound* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const BeginRound& from);
  void MergeFrom(const BeginRound& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(BeginRound* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // uint64 roundNumber = 1;
  void clear_roundnumber();
  static const int kRoundNumberFieldNumber = 1;
  ::google::protobuf::uint64 roundnumber() const;
  void set_roundnumber(::google::protobuf::uint64 value);

  // uint64 value = 2;
  void clear_value();
  static const int kValueFieldNumber = 2;
  ::google::protobuf::uint64 value() const;
  void set_value(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:libpaxos.BeginRound)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint64 roundnumber_;
  ::google::protobuf::uint64 value_;
  mutable int _cached_size_;
  friend struct protobuf_paxos_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Voted : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:libpaxos.Voted) */ {
 public:
  Voted();
  virtual ~Voted();

  Voted(const Voted& from);

  inline Voted& operator=(const Voted& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Voted& default_instance();

  static inline const Voted* internal_default_instance() {
    return reinterpret_cast<const Voted*>(
               &_Voted_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    3;

  void Swap(Voted* other);

  // implements Message ----------------------------------------------

  inline Voted* New() const PROTOBUF_FINAL { return New(NULL); }

  Voted* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Voted& from);
  void MergeFrom(const Voted& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Voted* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // uint64 roundNumber = 1;
  void clear_roundnumber();
  static const int kRoundNumberFieldNumber = 1;
  ::google::protobuf::uint64 roundnumber() const;
  void set_roundnumber(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:libpaxos.Voted)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint64 roundnumber_;
  mutable int _cached_size_;
  friend struct protobuf_paxos_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// NextRound

// uint64 roundNumber = 1;
inline void NextRound::clear_roundnumber() {
  roundnumber_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 NextRound::roundnumber() const {
  // @@protoc_insertion_point(field_get:libpaxos.NextRound.roundNumber)
  return roundnumber_;
}
inline void NextRound::set_roundnumber(::google::protobuf::uint64 value) {
  
  roundnumber_ = value;
  // @@protoc_insertion_point(field_set:libpaxos.NextRound.roundNumber)
}

// -------------------------------------------------------------------

// LastVote

// uint64 roundNumber = 1;
inline void LastVote::clear_roundnumber() {
  roundnumber_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 LastVote::roundnumber() const {
  // @@protoc_insertion_point(field_get:libpaxos.LastVote.roundNumber)
  return roundnumber_;
}
inline void LastVote::set_roundnumber(::google::protobuf::uint64 value) {
  
  roundnumber_ = value;
  // @@protoc_insertion_point(field_set:libpaxos.LastVote.roundNumber)
}

// uint64 lastRound = 2;
inline void LastVote::clear_lastround() {
  lastround_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 LastVote::lastround() const {
  // @@protoc_insertion_point(field_get:libpaxos.LastVote.lastRound)
  return lastround_;
}
inline void LastVote::set_lastround(::google::protobuf::uint64 value) {
  
  lastround_ = value;
  // @@protoc_insertion_point(field_set:libpaxos.LastVote.lastRound)
}

// -------------------------------------------------------------------

// BeginRound

// uint64 roundNumber = 1;
inline void BeginRound::clear_roundnumber() {
  roundnumber_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 BeginRound::roundnumber() const {
  // @@protoc_insertion_point(field_get:libpaxos.BeginRound.roundNumber)
  return roundnumber_;
}
inline void BeginRound::set_roundnumber(::google::protobuf::uint64 value) {
  
  roundnumber_ = value;
  // @@protoc_insertion_point(field_set:libpaxos.BeginRound.roundNumber)
}

// uint64 value = 2;
inline void BeginRound::clear_value() {
  value_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 BeginRound::value() const {
  // @@protoc_insertion_point(field_get:libpaxos.BeginRound.value)
  return value_;
}
inline void BeginRound::set_value(::google::protobuf::uint64 value) {
  
  value_ = value;
  // @@protoc_insertion_point(field_set:libpaxos.BeginRound.value)
}

// -------------------------------------------------------------------

// Voted

// uint64 roundNumber = 1;
inline void Voted::clear_roundnumber() {
  roundnumber_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 Voted::roundnumber() const {
  // @@protoc_insertion_point(field_get:libpaxos.Voted.roundNumber)
  return roundnumber_;
}
inline void Voted::set_roundnumber(::google::protobuf::uint64 value) {
  
  roundnumber_ = value;
  // @@protoc_insertion_point(field_set:libpaxos.Voted.roundNumber)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace libpaxos

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_paxos_2eproto__INCLUDED

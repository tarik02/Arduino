#include "List.h"

TList::TList()
{
First = 0;
};

TListItem *TList::GetItemData(int Index)
{
int TIndex = 0;
TListItem *TItem = First;

while(true)
{
if (TIndex == Index)
return TItem;

TItem = (TListItem *)TItem->Next;
TIndex++;
};
};
void TList::SetItemData(int Index,TListItem *Data)
{
int TIndex = 0;

if (!First)
First = new TListItem;

TListItem *TItem = First;



while(true)
{
if (TIndex == Index)
{
if (!TItem)
{
TItem = new TListItem;
GetItemData(TIndex - 1)->Next = TItem;
}

*TItem = *Data;
return;
};

TItem = (TListItem *)TItem->Next;
TIndex++;
};
};
int TList::Insert(int Index,void *Data)
{
TListItem *AItem = new TListItem;


AItem->Next = GetItemData(Index);

if (Index == 0)
{
First = AItem;
}
else
GetItemData(Index - 1)->Next = AItem;

AItem->Data = Data;
};
int TList::Add(void *Data)
{
TListItem *AItem = new TListItem;

AItem->Data = Data;
AItem->Next = 0;

SetItemData(Count(),AItem);
};
void TList::Delete(int Index)
{
  SetItemData(Index,GetItemData(Index + 1));
};
void TList::SetItem(int Index,void *Data)
{
GetItemData(Index)->Data = Data;
};
void *TList::GetItem(int Index)
{
return GetItemData(Index)->Data;
};
void TList::Clear()
{
for (int i = 0; i < Count(); i++)
Delete(i);
};
int TList::Count()
{
int Result = 0;
TListItem *Item = First;

while (Item)
{
Result++;
Item = (TListItem *)Item->Next;
};
return Result;
};


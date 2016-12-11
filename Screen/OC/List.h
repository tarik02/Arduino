#ifndef ListH
#define ListH

struct TListItem
{
  void *Next;
  void *Data;
};

class TList
{
private:
TListItem *First;

TListItem *GetItemData(int Index);
void SetItemData(int Index,TListItem *Data);
public:
TList();

int Insert(int Index,void *Data);
int Add(void *Data);
void Delete(int Index);

void Clear();
int Count();

void SetItem(int Index,void *Data);
void *GetItem(int Index);
};


#endif


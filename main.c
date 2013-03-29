#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"


BOOK * HWBook;
typedef struct
{
  BOOK * book;
}MSG;

int TerminateElf(void * ,BOOK* book)
{
  FreeBook(book);
  return(1);
}

int ShowAuthorInfo(void *mess ,BOOK* book)
{
  MSG * msg = (MSG*)mess;
  MessageBox(EMPTY_SID,STR("VideoLandscape"), NOIMAGE, 1, 5000,msg->book);
  return(1);
}

int OnVidoe(void *mess ,BOOK* book)
{
  if(FindBook( get_IsMediaPlayerVideoBook() ))
  {
    int Orentation = BookObj_GetDisplayOrientation(FindBook(get_IsMediaPlayerVideoBook()));
    if(Orentation == 0)
    {
      BookObj_SetDisplayOrientation( FindBook( get_IsMediaPlayerVideoBook() ), 1 );
    }
  }
  return(1);
}

const PAGE_MSG HW_PageEvents[]@ "DYN_PAGE" ={
  UI_MEDIAPLAYER_VIDEO_CREATED_EVENT_TAG , OnVidoe,
  ELF_TERMINATE_EVENT , TerminateElf,
  ELF_SHOW_INFO_EVENT  , ShowAuthorInfo,
  0,0
};

PAGE_DESC base_page ={"VideoLandscape_Base",0,HW_PageEvents};

void elf_exit(void)
{
  kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
}

void onCloseHWBook(BOOK * book)
{
  if (book)
  {
    SUBPROC(elf_exit);
  }
}

BOOK * CreateHWBook()
{
  HWBook= new BOOK;
  CreateBook(HWBook,onCloseHWBook,&base_page,"VideoLandscape",-1,0);
  return(HWBook);
}

int main (void)
{
  CreateHWBook();
  return(0);
}

#include <string>
#include <string_view>
#include "test_runner.h"
#include <deque>
#include <algorithm>
#include <ostream>
#include <iterator>
#include "profile.h"
#include <list>

using namespace std;

//Если редактор содержит текст длиной n символов, то курсор может находиться в одной из (n + 1) возможных позиций.
//Например, обозначим курсор вертикальной чертой | (это обозначение мы будем использовать в дальнейшем),
//тогда в тексте abc курсор может располагаться в 4 позициях: |abc, a|bc, ab|c, abc|.
//Поэтому команда Left не имеет эффекта, когда курсор расположен в начале текста, а Right не имеет эффекта, когда курсор находится в конце.
//В частности, ни Left, ни Right не имеют эффекта, когда редактор не содержит текста.

//Введённый символ располагается в позиции курсора, сдвигая курсор и весь текст справа от него на одну позицию вправо.
//Аналогично, при вставке фрагмента длиной n курсор и текст справа от него смещаются на n позиций вправо.
//В таблице ниже приведены примеры, демонстрирующие данное правило.

//Буфер обмена изначально пуст. Вставка пустого фрагмента не имеет эффекта.
//Содержимое буфера не сбрасывается после вставки, а остается неизменным до следующей команды Copy или Cut.
//Копирование или вырезание фрагмента нулевой длины не оказывает влияния на текст, но опустошает буфер обмена.
//Курсор не смещается ни при копировании, ни при вырезании текста.
//Например, после вырезания из текста ab|cdef фрагмента из трёх символов, получим текст ab|f.

//В комментариях к методам Cut(size_t tokens) и Copy(size_t tokens) указано, что
//в буфер обмена попадает фрагмент длиной не более tokens символов — это означает, что, если справа
//от курсора располагается менее, чем tokens символов, методы Cut() и Copy() должны вырезать/скопировать все символы справа.

//Ограничения
//Реализация класса Editor должна обрабатывать 10^6 запросов не более чем за 1 секунду. При этом гарантируется, что:

//длина текста никогда не превышает 10^6 символов;
//методы Copy() и Cut() суммарно копируют/вырезают не более 10^6 символов;
//метод GetText() вызывается один раз в каждом из тестов.

//static string gapBuffer(1000000,' ');






//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Это решение медленное ,прошло за 1.33, deque<char> быстро добавляет, но каждый раз выделять память под символ долго


//class Editor {
//public:
//    using  PosIt = deque<char>::iterator ;
//    Editor()
//    {
//        gapBuffer.resize(100000);
//        startBufChunk = 0;
//        endBufChunk = 0;
//    }
//    // сдвинуть курсор влево
//    inline void Left()
//    {
//        if(pos>0) --pos;
//    }
//    // сдвинуть курсор вправо
//    inline void Right()
//    {
//        if(pos<text.size()) ++pos;
//    }
//    // вставить символ token
//    inline void Insert(char token)
//    {
//        text.insert(text.begin()+pos,1,token);
//        ++pos;
//    }
//    inline void updateBuf()
//    {
//        startBufChunk=endBufChunk;
//    }

//    inline PosIt startCursorPos()
//    {
//        return text.begin()+pos;
//    }

//    inline PosIt endCursorPos(size_t tokens)
//    {
//        return min(startCursorPos()+tokens, text.end());
//    }

//    inline void copyToBuf(size_t tokens)
//    {
//        copy(startCursorPos(), endCursorPos(tokens), gapBuffer.begin()+endBufChunk);
//        endBufChunk += endCursorPos(tokens) - startCursorPos();
//    }

//    // cкопировать не более tokens символов, начиная с текущей позиции курсора
//    void Copy(size_t tokens)
//    {
//        updateBuf();
//        if(!tokens) return;
//        copyToBuf(tokens);
//    }
//    // вырезать не более tokens символов, начиная с текущей позиции курсора
//    void Cut(size_t tokens)
//    {
//        updateBuf();
//        if(!tokens) return;
//        copyToBuf(tokens);
//        text.erase(startCursorPos(), endCursorPos(tokens));
//    }
//    // вставить содержимое буфера в текущую позицию курсора
//    void Paste()
//    {
//        if(startBufChunk==endBufChunk) return;
//        text.insert(startCursorPos(), gapBuffer.begin()+startBufChunk, gapBuffer.begin()+endBufChunk);
//        pos += endBufChunk-startBufChunk;
//    }
//    // получить текущее содержимое текстового редактора
//    string GetText() const
//    {
//        string ret;
//        ret.resize(text.size());
//        copy(text.begin(), text.end(), begin(ret));
//        return ret;
//    }
//    int bufsize() {return gapBuffer.size();}

////    void printBuf()
////    {
////        for(auto it=gapBuffer.begin()+startBufChunk; it!=gapBuffer.begin()+endBufChunk; it++)
////        {
////            cout<<*it;
////        }
////        cout<<endl;
//////        std::copy(gapBuffer.begin()+startBufChunk, gapBuffer.begin()+endBufChunk,
//////                  std::ostream_iterator<int>(std::cout, " "));
////    }
//private:
//    deque<char> text;
//    //string gapBuffer;
//    int startBufChunk;
//    int endBufChunk;
//    int pos = 0;
//};

//Мое решение
//Следующее решение лучше, прошло за 0.02,  мы используем GapBuffer , его часто используют в текстовых редакторах
//Мы заранее выделили память под 1000'000 символов и храним gap в 1000'000 символов
//class Editor {
//public:
//    using Buffer = array<char,1000000>;
//    using bufIt = Buffer::iterator;
//    size_t GAP_SIZE = 1000000;
//    Editor()
//    {
//        point = buffer.begin();
//        bufstart = buffer.begin();
//        bufend = buffer.end();
//        gapstart = buffer.begin();
//        gapend = bufend;
//        tempStart = tempBuffer.begin();
//        tempEnd = tempBuffer.begin();
//    }
//    void Left()
//    {
//        if(point == bufstart)
//            return;
//        if(point == gapend){
//            point = gapstart;
//        }
//        (--point);
//    }
//    void Right()
//    {
//        if(point==bufend)
//        {
//            return ;
//        }
//        if(point == gapstart)
//        {
//            point = gapend;
//        }
//         if(point!=bufend) (++point);
//    }
//    inline void updateTempBuf()
//    {
//        tempEnd=tempStart;
//    }
//    inline bufIt endCursorPos(size_t tokens)
//    {
//        return min(point+tokens, bufend);
//    }
//    void Insert(char token)
//    {
//        if(point!=gapstart) {
//            MoveGapToPoint();
//        }
//        *(gapstart++) = token;
//        point++;
//    }

//    void Delete(size_t size)
//    {
//        if(point!=gapstart){
//            MoveGapToPoint();
//        }
//        gapend = min(gapend+size, bufend);
//    }
//    void Copy(size_t tokens)
//    {
//        updateTempBuf();
//        if(!tokens) return;
//        if(point > gapstart){
//            copy(point, endCursorPos(tokens), tempStart);
//            tempEnd = tempStart+tokens;
//        }else {
//            ptrdiff_t distBef = min(size_t(gapstart-point), tokens);
//            ptrdiff_t distAfter = min(tokens-distBef, (size_t)(bufend-gapend));
//            copy(point, gapstart, tempStart);
//            tempEnd = tempStart+distBef;
//            copy(gapend,gapend+distAfter,tempEnd);
//            tempEnd += distAfter;
//        }
//    }
//    void Cut(size_t tokens)
//    {
//        Copy(tokens);
//        Delete(tokens);
//    }
//    void Paste()
//    {
//        if(tempStart==tempEnd) return;
//        for(auto it = tempStart; it!=tempEnd; it++)
//        {
//            Insert(*it);
//        }
//    }
//    string GetText() const
//    {
//        string_view s1(bufstart, gapstart-bufstart);
//        string_view s2(gapend, bufend-gapend);
//        string ret;
//        ret.reserve(sizeBuf());
//        return (ret += s1)+=s2;
//    }

//    int moveBytes(bufIt dest, bufIt source, size_t length)
//    {
//        if(dest==source || length==0) return 1;
//        if(source > dest) {
//            if(source+length > bufend){
//                cout<<"go beyond the buffer length = "<<length<<endl;
//                return 0;
//            }
//            for(;length>0; length--){
//                *(dest++) = *(source++);
//            }
//        }
//        else {
//            source += length;
//            dest += length;
//            for(;length >0; length--){
//                *(--dest) = *(--source);
//            }
//        }
//        return 1;
//    }
//    void MoveGapToPoint()
//    {
//        if(point==gapstart) return;
//        if(point==gapend){
//            point = gapstart;
//            return;
//        }
//        if(point<gapstart){
//            moveBytes(point + (gapend-gapstart), point, gapstart-point);
//            gapend -= gapstart-point;
//            gapstart = point;
//        }else {
//            moveBytes(gapstart, gapend, point-gapend);
//            gapstart += point-gapend;
//            gapend = point;
//            point = gapstart;
//        }
//    }
//    int sizeGap() const
//    {
//        return gapend-gapstart;
//    }
//    int sizeBuf() const
//    {
//        return (bufend-bufstart)-sizeGap();
//    }
//    string getTempBuf()
//    {
//        return string(tempStart, tempEnd);
//    }
//private:
//    Buffer buffer;
//    bufIt bufstart;
//    bufIt bufend;
//    bufIt point;
//    bufIt gapstart;
//    bufIt gapend;
//    Buffer tempBuffer;
//    bufIt tempStart;
//    bufIt tempEnd;
//};

//Решение авторов
//Их решение прошло за 0.15 , медленее чем gapBuffer, но намного проще, list из симолов)
class Editor {
public:
  Editor()
    : pos(text.end()) {
  }

  void Left() {
    pos = Advance(pos, -1);
  }

  void Right() {
    pos = Advance(pos, 1);
  }

  void Insert(char token) {
    text.insert(pos, token);
  }

  void Cut(size_t tokens = 1) {
    auto pos2 = Advance(pos, tokens);
    buffer.assign(pos, pos2);
    pos = text.erase(pos, pos2);
  }

  void Copy(size_t tokens = 1) {
    auto pos2 = Advance(pos, tokens);
    buffer.assign(pos, pos2);
  }

  void Paste() {
    text.insert(pos, buffer.begin(), buffer.end());
  }

  string GetText() const {
    return {text.begin(), text.end()};
  }

private:
  using Iterator = list<char>::iterator;
  list<char> text;
  list<char> buffer;
  Iterator pos;

  Iterator Advance(Iterator it, int steps) const {
    while (steps > 0 && it != text.end()) {
      ++it;
      --steps;
    }
    while (steps < 0 && it != text.begin()) {
      --it;
      ++steps;
    }
    return it;
  }
};

void TypeText(Editor& editor, const string& text)
{
    for(char c: text){
        editor.Insert(c);
    }
}

void TestNextPrev()
{
    Editor editor;
    TypeText(editor, "Archi");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Insert('u');
    ASSERT_EQUAL(editor.GetText(),"Aruchi");
    editor.Right();
    editor.Insert('s');
    ASSERT_EQUAL(editor.GetText(),"Arucshi");
    editor.Right();
    editor.Right();
    editor.Right();
    editor.Right();
    editor.Insert('m');
    ASSERT_EQUAL(editor.GetText(),"Arucshim");

    editor.Right();
    editor.Right();
    editor.Right();
    editor.Insert('a');
    ASSERT_EQUAL(editor.GetText(),"Arucshima");

}
void TestInsert()
{
    Editor editor;
    TypeText(editor, "Felix");
    editor.Insert('a');
    editor.Insert('b');
    ASSERT_EQUAL(editor.GetText(),"Felixab");
    editor.Left();
    editor.Left();
    editor.Insert('c');
    editor.Insert('d');
    ASSERT_EQUAL(editor.GetText(),"Felixcdab");
    editor.Right();
    editor.Right();
    editor.Right();
    editor.Right();
    ASSERT_EQUAL(editor.GetText(),"Felixcdab");
    editor.Insert('c');
    ASSERT_EQUAL(editor.GetText(),"Felixcdabc");

}

void TestEditing()
{
  {
//    LOG_DURATION();
//    for(int i=0; i<100000; i++)
//    {
//        Editor editor;

//        const size_t text_len = 12;
//        const size_t first_part_len = 7;
//        TypeText(editor, "hello, world");
//        for(size_t i = 0; i < text_len; ++i) {
//          editor.Left();
//        }

//        editor.Cut(first_part_len);
//        for(size_t i = 0; i < text_len - first_part_len; ++i) {
//          editor.Right();
//        }
//        TypeText(editor, ", ");

//        editor.Paste();
//        editor.Left();
//        editor.Left();
//        editor.Cut(3);
//        string c = editor.GetText();
//    }



    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }

    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    ASSERT_EQUAL(editor.GetText(), "world, ");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "world, hello, ");
    editor.Left();
    editor.Left();
    editor.Cut(3);
    string c = editor.GetText();
    ASSERT_EQUAL(editor.GetText(), "world, hello");

  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

void MyTest()
{
    Editor editor;
    editor.Right();
    editor.Insert('a');
    editor.Right();
    editor.Left();
    editor.Copy(1);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "aa");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "a");
    editor.Copy(2);
    editor.Insert('b');
    editor.Cut(0);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "ba");
    editor.Right();
    editor.Insert('c');
    editor.Left();
    editor.Left();
    editor.Copy(1);
    editor.Right();
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "baac");
    editor.Copy(1);
    editor.Paste();
    editor.Right();
    ASSERT_EQUAL(editor.GetText(), "baacc");

}

//int main() {
//  TestRunner tr;
//  RUN_TEST(tr, TestEditing);
//  RUN_TEST(tr, TestNextPrev);
//  RUN_TEST(tr, TestInsert);
//  RUN_TEST(tr, TestReverse);
//  RUN_TEST(tr, TestNoText);
//  RUN_TEST(tr, TestEmptyBuffer);
//  RUN_TEST(tr, MyTest);
//  return 0;
//}


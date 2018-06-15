#if defined(_WIN32_) || defined(_WIN64_)
void clearScreen(){
  system("cls");
}
#else
void clearScreen(){
  system("clear");
}
#endif

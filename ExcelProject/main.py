from course import courseMenu
from manager import managerMenu
from mappingCourseTrainee import mappingCourseTraineeMenu
from mappingCourseTrainer import mappingCourseTrainerMenu
from session import sessionMenu
from trainee import traineeMenu
from trainer import trainerMenu

choice=69;
while (choice!=0):
    print("1. ""ListOfTrainees"" Menu")
    print("2. ""TrainerDetails"" Menu")
    print("3. ""CourseDetails"" Menu")
    print("4. ""ManagerDetails"" Menu")
    print("5. ""MappingCourseTrainer"" Menu")
    print("6. ""MappingCourseTrainee"" Menu")
    print("7. Session Menu")
    print("8. Exit")

    choice = input("Enter your choice: ")

    if choice == '1':
        traineeMenu()
    elif choice == '2':
        trainerMenu()
        break
    elif choice == '3':
        courseMenu()
    elif choice == '4':
        managerMenu()
    elif choice=='5':
        mappingCourseTrainerMenu()
        break
    elif choice=='6':
        mappingCourseTraineeMenu()
        break
    elif choice=='7':
        sessionMenu()
        break
    elif choice == '8':
        break
    else:
        print("Invalid choice. Please try again.")
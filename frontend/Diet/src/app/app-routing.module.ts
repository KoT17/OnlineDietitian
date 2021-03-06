import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { HomeComponent } from './home/home.component';
import { UserHomeComponent } from './user-home/user-home.component';
import { ContactComponent } from './contact/contact.component';
import { ServicesComponent } from './services/services.component';
import { SignInComponent } from './sign-in/sign-in.component';
import { RegisterComponent } from './register/register.component';
import { SurveyComponent } from './survey/survey.component';
import { PickdietComponent } from './pickdiet/pickdiet.component';


const routes: Routes = [
  { path: "home", component: HomeComponent },
  { path: "", redirectTo: "home", pathMatch: "full" },
  { path: "authhome", component: UserHomeComponent },
  { path: "contactUs", component: ContactComponent },
  { path: "services", component: ServicesComponent },
  { path: "manage", component: SurveyComponent },
  { path: "signIn", component: SignInComponent },
  { path: "reg", component: RegisterComponent },
  { path: "survey", component: SurveyComponent },
  { path: "pick", component: PickdietComponent }
  ];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }

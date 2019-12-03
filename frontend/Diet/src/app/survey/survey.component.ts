import { Component, OnInit } from '@angular/core';
import { SignInService } from '../sign-in.service';
import { Router } from '@angular/router';
import { FormGroup, FormControl, Validators } from '@angular/forms';
import { HttpClient, HttpHeaders, HttpErrorResponse } from '@angular/common/http';
import { take, catchError } from 'rxjs/operators';
import { throwError } from 'rxjs';
declare var moment: any;

@Component({
  selector: 'app-survey',
  templateUrl: './survey.component.html',
  styleUrls: ['./survey.component.css']
})
export class SurveyComponent implements OnInit {
  title: string;
  survey = new FormGroup({
    height: new FormControl("", [Validators.required]),
    weight: new FormControl("", [Validators.required]),
    gender: new FormControl("", [Validators.required]),
    DOB: new FormControl("", [Validators.required]),
    lvlOfActivity: new FormControl("", [Validators.required]),
    dietaryRestriction: new FormControl("", [Validators.required])
  });
  constructor(private signInService: SignInService, private router: Router, private http: HttpClient) {
    if(router.url == "/manage") {
      this.title = "Update your information!"
    } else {
      this.title = "Tell us more!";
    }
  }

  ngOnInit() {
  }
  submit() : void {
      this.http.post("http://localhost:4201/NutritionalLookup", {}, { headers: new HttpHeaders({
        source: 'survey',
        user: this.signInService.getUser().email,
        password: this.signInService.getUser().password,
        email: this.signInService.getUser().email,
        height: this.survey.get('height').value.toString(),
        weight: this.survey.get('weight').value.toString(),
        gender: this.survey.get('gender').value,
        DOB: new moment(this.survey.get('DOB').value).format('YYYY-MM-DDTHH:mm:ss:SSS[Z]'),
        lvlOfActivity: this.survey.get('lvlOfActivity').value,
        dietaryRestriction: this.convertDiet(this.survey.get('dietaryRestriction').value).toString(),
        surveyTimeTaken: new moment(new Date()).format('YYYY-MM-DDTHH:mm:ss:SSS[Z]'),
      })}).pipe(take(1)).pipe(catchError(this.handleError)).subscribe(() => {
        this.router.navigate(["pick"]);
      })
   }

   handleError(error: HttpErrorResponse) {
     alert('Survey submission failed!');
     return throwError('');
   }

   convertDiet(diet): number {
     let number: number;
     switch(diet) {
       case "None":
         number = 0;
         break;
       case "Vegan":
         number = 1;
         break;
       case "Vegetarian":
         number = 2;
         break;
       case "Gluten Free":
         number = 3;
         break;
       default:
         break;
     }
     return number;
   }
}
